package fr.epita.assistants.jws.domain.service;

import fr.epita.assistants.jws.converter.GameModelConverter;
import fr.epita.assistants.jws.converter.RleConverter;
import fr.epita.assistants.jws.data.model.GameModel;
import fr.epita.assistants.jws.data.model.PlayerModel;
import fr.epita.assistants.jws.data.repository.GameRepository;
import fr.epita.assistants.jws.data.repository.PlayerRepository;
import fr.epita.assistants.jws.domain.entity.GameEntity;
import fr.epita.assistants.jws.utils.Game;
import fr.epita.assistants.jws.utils.GameState;
import fr.epita.assistants.jws.utils.Player;
import io.quarkus.hibernate.orm.panache.PanacheQuery;
import lombok.Getter;
import lombok.SneakyThrows;
import org.eclipse.microprofile.config.inject.ConfigProperty;

import javax.enterprise.context.ApplicationScoped;
import javax.inject.Inject;
import javax.transaction.Transactional;
import java.io.*;
import java.sql.Timestamp;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

@Getter
@ApplicationScoped

public class GameService {
    @Inject
    GameRepository gameRepository;
    @Inject
    GameModelConverter gameModelConverter;
    @Inject
    PlayerRepository playerRepository;
    @Inject
    RleConverter rleConverter;

    @ConfigProperty(name = "JWS_MAP_PATH")
    String JWS_MAP_PATH;

    @ConfigProperty(name = "JWS_TICK_DURATION")
    Long JWS_TICK_DURATION;

    @ConfigProperty(name = "JWS_DELAY_MOVEMENT")
    Long JWS_DELAY_MOVEMENT;

    @ConfigProperty(name = "JWS_DELAY_BOMB")
    Long JWS_DELAY_BOMB;

    @SneakyThrows
    private List<String> exportMap() {
        List<String> res = new ArrayList<>();
        BufferedReader bufferedReader = new BufferedReader(new FileReader(JWS_MAP_PATH));
        String line;
        while ((line = bufferedReader.readLine()) != null) {
            res.add(line);
        }
        return res;
    }

    @Transactional
    public Game createGame(String name) {
        PlayerModel player = new PlayerModel().withName(name).withPosX(1).withPosY(1).withLives(3);
        GameModel game =
                new GameModel().withStarttime(Timestamp.from(Instant.now())).withState(String.valueOf(GameState.STARTING)).withMap(exportMap());
        player.setGameModel(game);
        List<PlayerModel> players = new ArrayList<>();
        playerRepository.persist(player);
        players.add(player);
        game.setPlayers_id(players);

        gameRepository.persist(game);
        List<Player> playerList = new ArrayList<>();
        playerList.add(new Player().withName(player.getName()).withId(player.getId()).withPosY(player.getPosY()).withPosX(player.getPosX()).withLives(player.getLives()));
        return new Game().withId(game.getId()).withStarttime(game.getStarttime()).withState(GameState.valueOf(game.getState())).withMap(game.getMap()).withPlayers_id(playerList);
    }

    public List<GameEntity> getGameRepository() {
        List<GameEntity> gameEntities = new ArrayList<>();
        PanacheQuery<GameModel> panacheQuery = gameRepository.findAll();
        panacheQuery.stream().toList().forEach(C -> gameEntities.add(gameModelConverter.convertToGameEntity(C)));
        return gameEntities;
    }

    public Game getSpecificGameRepository(Long gameId) {
        GameModel gameModel = gameRepository.findById(gameId);
        return gameModel == null ? null : gameModelConverter.convertToGame(gameModel);
    }

    @Transactional
    public Game joinGame(String name, Long id) {
        GameModel gameModel = gameRepository.findById(id);
        if (gameModel == null)
            return null;
        if (gameModel.getState().compareTo("STARTING") != 0 || gameModel.getPlayers_id().size() == 4)
            return new Game().withId(null);
        PlayerModel player = new PlayerModel().withName(name).withLives(3);
        if (gameModel.getPlayers_id().size() == 1) {
            player.setPosX(15);
            player.setPosY(1);
        } else if (gameModel.getPlayers_id().size() == 2) {
            player.setPosX(15);
            player.setPosY(13);
        } else if (gameModel.getPlayers_id().size() == 3) {
            player.setPosX(1);
            player.setPosY(13);
        }
        playerRepository.persist(player);
        List<PlayerModel> tmp = new ArrayList<>(gameModel.getPlayers_id());
        tmp.add(player);
        gameModel.setPlayers_id(tmp);
        gameModel.setMap(rleConverter.copyMap(gameModel.getMap()));
        gameRepository.persist(gameModel);
        List<Player> playerList = new ArrayList<>();
        tmp.forEach(player1 -> playerList.add(new Player().withName(player1.getName()).withId(player1.getId()).withPosY(player1.getPosY()).withPosX(player1.getPosX()).withLives(player1.getLives())));
        return new Game().withId(gameModel.getId()).withState(GameState.valueOf(gameModel.getState())).withStarttime(gameModel.getStarttime()).withMap(gameModel.getMap()).withPlayers_id(playerList);
    }

    @Transactional
    public Game startGame(Long gameId) {
        GameModel gameModel = gameRepository.findById(gameId);
        if (gameModel == null || gameModel.getState().compareTo("FINISHED") == 0)
            return null;
        if (gameModel.getPlayers_id().size() == 1)
            gameModel.setState("FINISHED");
        else
            gameModel.setState("RUNNING");
        gameModel.setMap(exportMap());
        gameRepository.persist(gameModel);
        return gameModelConverter.convertToGame(gameModel);

    }

    @Transactional
    public Game movePlayer(Long gameId, Long playerId, Integer posX, Integer posY) {
        GameModel gameModel = gameRepository.findById(gameId);
        PlayerModel playerModel = playerRepository.findById(playerId);
        List<String> decoded = rleConverter.rleToNormal(gameModel.getMap());
        if (gameModel.getState().compareTo("RUNNING") != 0 || playerModel.getLives() == 0 || Math.abs(playerModel.getPosX() - posX) + Math.abs(playerModel.getPosY() - posY) > 1 || decoded.get(posY).charAt(posX) != 'G')
            return new Game().withId(null);
        if (playerModel.getLastmovement() != null && RleConverter.comparerTimestamps(playerModel.getLastmovement(), JWS_TICK_DURATION * JWS_DELAY_BOMB))
            return new Game().withPlayers_id(null).withId(2L);
        playerModel.setPosX(posX);
        playerModel.setPosY(posY);
        playerModel.setLastmovement(Timestamp.from(Instant.now()));
        playerRepository.persist(playerModel);
        List<PlayerModel> updatedList = new ArrayList<>();
        List<Player> playerList = new ArrayList<>();
        gameModel.getPlayers_id().forEach(L -> {
            if (L.getId().equals(playerModel.getId())) {
                updatedList.add(playerModel);
                playerList.add(new Player().withName(playerModel.getName()).withId(playerModel.getId()).withPosY(playerModel.getPosY()).withPosX(playerModel.getPosX()).withLives(playerModel.getLives()));
            } else {

                updatedList.add(L);
                playerList.add(new Player().withName(L.getName()).withId(L.getId()).withPosY(L.getPosY()).withPosX(L.getPosX()).withLives(L.getLives()));
            }
        });
        gameModel.setPlayers_id(updatedList);
        gameRepository.persist(gameModel);
        return new Game().withId(gameModel.getId()).withState(GameState.valueOf(gameModel.getState())).withStarttime(gameModel.getStarttime()).withMap(gameModel.getMap()).withPlayers_id(playerList);
    }

    public boolean exists(Long gameId, Long playerId) {
        return (gameRepository.findById(gameId) == null || playerRepository.findById(playerId) == null);
    }

    @Transactional
    public Game putBomb(Long gameId, Long playerId, Integer posX, Integer posY) {
        GameModel gameModel = gameRepository.findById(gameId);
        PlayerModel playerModel = playerRepository.findById(playerId);
        if (gameModel.getState().compareTo("RUNNING") != 0 || playerModel.getLives() == 0 || Math.abs(playerModel.getPosX() - posX) + Math.abs(playerModel.getPosY() - posY) != 0)
            return new Game().withId(null);
        if (playerModel.getLastbomb() != null && RleConverter.comparerTimestamps(playerModel.getLastbomb(), JWS_TICK_DURATION * JWS_DELAY_BOMB))
            return new Game().withPlayers_id(null).withId(2L);
        playerModel.setLastbomb(Timestamp.from(Instant.now()));
        playerRepository.persist(playerModel);
        List<String> decoded = rleConverter.rleToNormal(gameModel.getMap());
        String Y = decoded.get(posY).substring(0, posX) + 'B' + decoded.get(posY).substring(posX + 1);
        List<String> updatedMap = new ArrayList<>();
        AtomicInteger i = new AtomicInteger();
        decoded.forEach(D -> {
            if (i.get() == posY) {
                updatedMap.add(Y);
            }
            else
                updatedMap.add(D);
            i.getAndIncrement();
        });

        List<PlayerModel> updatedList = new ArrayList<>();
        List<Player> playerList = new ArrayList<>();
        gameModel.getPlayers_id().forEach(L -> {
            if (L.getId().equals(playerModel.getId())) {
                updatedList.add(playerModel);
                playerList.add(new Player().withName(playerModel.getName()).withId(playerModel.getId()).withPosY(playerModel.getPosY()).withPosX(playerModel.getPosX()).withLives(playerModel.getLives()));
            } else {

                updatedList.add(L);
                playerList.add(new Player().withName(L.getName()).withId(L.getId()).withPosY(L.getPosY()).withPosX(L.getPosX()).withLives(L.getLives()));
            }
        });
        gameModel.setPlayers_id(updatedList);
        gameModel.setMap(rleConverter.normalToRle(updatedMap));
        gameRepository.persist(gameModel);
        return new Game().withId(gameModel.getId()).withState(GameState.valueOf(gameModel.getState())).withStarttime(gameModel.getStarttime()).withMap(gameModel.getMap()).withPlayers_id(playerList);
    }
}

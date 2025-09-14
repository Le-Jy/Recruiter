package fr.epita.assistants.jws.converter;

import fr.epita.assistants.jws.data.model.GameModel;
import fr.epita.assistants.jws.domain.entity.GameEntity;
import fr.epita.assistants.jws.utils.Game;
import fr.epita.assistants.jws.utils.GameState;
import fr.epita.assistants.jws.utils.Player;

import javax.enterprise.context.ApplicationScoped;
import java.util.ArrayList;
import java.util.List;

@ApplicationScoped
public class GameModelConverter {
    public GameEntity convertToGameEntity(GameModel gameModel) {
        GameEntity gameEntity = new GameEntity();
        gameEntity.setId(gameModel.getId());
        gameEntity.setStarttime(gameModel.getStarttime());
        gameEntity.setState(GameState.valueOf(gameModel.getState()));
        gameEntity.setNb_players(gameModel.getPlayers_id().size());
        return gameEntity;
    }

    public Game convertToGame(GameModel gameModel) {
        List<Player> playerList = new ArrayList<>();
        gameModel.getPlayers_id().forEach(C -> playerList.add(new Player().withId(C.getId()).withName(C.getName()).withLives(C.getLives()).withPosX(C.getPosX()).withPosY(C.getPosY())));
        return new Game().withId(gameModel.getId()).withMap(gameModel.getMap()).withPlayers_id(playerList).withStarttime(gameModel.getStarttime()).withState(GameState.valueOf(gameModel.getState()));
    }
}

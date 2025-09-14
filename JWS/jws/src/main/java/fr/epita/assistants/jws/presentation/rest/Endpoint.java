package fr.epita.assistants.jws.presentation.rest;

import fr.epita.assistants.jws.domain.entity.GameEntity;
import fr.epita.assistants.jws.domain.service.GameService;
import fr.epita.assistants.jws.presentation.rest.request.CreateGameRequest;
import fr.epita.assistants.jws.presentation.rest.request.JoinGameRequest;
import fr.epita.assistants.jws.presentation.rest.request.MovePlayerRequest;
import fr.epita.assistants.jws.presentation.rest.response.GameDetailResponse;
import fr.epita.assistants.jws.presentation.rest.response.GameListResponse;
import fr.epita.assistants.jws.utils.Game;
import lombok.SneakyThrows;

import javax.inject.Inject;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.util.ArrayList;
import java.util.List;

@Path("/")
@Produces(MediaType.APPLICATION_JSON)
@Consumes(MediaType.APPLICATION_JSON)
public class Endpoint {
    @Inject
    GameService gameService;
    @GET
    @Path("games")
    @SneakyThrows
    public Response getGames() {
        //Get all games
        List<GameEntity> gameEntityList = gameService.getGameRepository();
        List<GameListResponse> gameListResponses = new ArrayList<>();
        gameEntityList.forEach(C -> gameListResponses.add(new GameListResponse().withState(String.valueOf(C.getState()))
                .withId(C.getId())
                .withPlayers(C.getNb_players())));
        return Response.ok(gameListResponses).build();
    }

    @POST
    @Path("games")
    @SneakyThrows
    public Response postGames(CreateGameRequest createGameRequest) {
        //Create new game
        if (createGameRequest == null || createGameRequest.getName() == null)
            return Response.status(Response.Status.BAD_REQUEST).build();
        String name = createGameRequest.getName();
        Game newGame = gameService.createGame(name);
        GameDetailResponse newGameDetailResponse = new GameDetailResponse().withId(newGame.getId()).withPlayers(newGame.getPlayers_id()).withMap(newGame.getMap()).withState(String.valueOf(newGame.getState())).withStartTime(newGame.getStarttime());
        return Response.ok(newGameDetailResponse).build();
    }
    @GET
    @Path("games/{gameId}")
    @SneakyThrows
    public Response getGamesId(@PathParam("gameId") Long gameId) {
        //Get game info
        Game game = gameService.getSpecificGameRepository(gameId);
        if (game == null)
            return Response.status(Response.Status.NOT_FOUND).build();
        GameDetailResponse newGameDetailResponse = new GameDetailResponse().withState(String.valueOf(game.getState())).withId(game.getId()).withMap(game.getMap()).withPlayers(game.getPlayers_id()).withStartTime(game.getStarttime());
        return Response.ok(newGameDetailResponse).build();
    }

    @POST
    @Path("games/{gameId}")
    @SneakyThrows
    public Response postGamesId(@PathParam("gameId") Long gameId, JoinGameRequest joinGameRequest) {
        //Join a game
        if (joinGameRequest == null || joinGameRequest.getName() == null)
            return Response.status(Response.Status.BAD_REQUEST).build();
        String name = joinGameRequest.getName();
        Game game = gameService.joinGame(name, gameId);
        if (game == null)
            return Response.status(Response.Status.NOT_FOUND).build();
        if (game.getId() == null)
            return Response.status(Response.Status.BAD_REQUEST).build();
        GameDetailResponse gameDetailResponse = new GameDetailResponse().withState(String.valueOf(game.getState())).withId(game.getId()).withMap(game.getMap()).withPlayers(game.getPlayers_id()).withStartTime(game.getStarttime());
        return Response.ok(gameDetailResponse).build();
    }
    @PATCH
    @Path("games/{gameId}/start")
    @SneakyThrows
    public Response patchGamesIdStart(@PathParam("gameId") Long gameId) {
        //Start game
        Game newGame = gameService.startGame(gameId);
        if (newGame == null)
            return Response.status(Response.Status.NOT_FOUND).build();
        GameDetailResponse newGameDetailResponse = new GameDetailResponse().withId(newGame.getId()).withPlayers(newGame.getPlayers_id()).withMap(newGame.getMap()).withState(String.valueOf(newGame.getState())).withStartTime(newGame.getStarttime());
        return Response.ok(newGameDetailResponse).build();
    }

    @POST
    @Path("/games/{gameId}/players/{playerId}/move")
    @SneakyThrows
    public Response postMovePlayer(@PathParam("gameId") Long gameId, @PathParam("playerId") Long playerId, MovePlayerRequest movePlayerRequest) {
        if (gameService.exists(gameId, playerId))
            return Response.status(Response.Status.NOT_FOUND).build();

        if (movePlayerRequest == null || movePlayerRequest.getPosX() == null || movePlayerRequest.getPosY() == null) {
            return Response.status(Response.Status.BAD_REQUEST).build();
        }
        Game updatedGame = gameService.movePlayer(gameId, playerId, movePlayerRequest.getPosX(), movePlayerRequest.getPosY());

        if (updatedGame.getId() == null) {
            return Response.status(Response.Status.BAD_REQUEST).build();

        }
        if (updatedGame.getPlayers_id() == null)
            return Response.status(Response.Status.TOO_MANY_REQUESTS).build();
        GameDetailResponse newUpdatedDetailResponse = new GameDetailResponse().withId(updatedGame.getId()).withPlayers(updatedGame.getPlayers_id()).withMap(updatedGame.getMap()).withState(String.valueOf(updatedGame.getState())).withStartTime(updatedGame.getStarttime());
        return Response.ok(newUpdatedDetailResponse).build();
    }

    @POST
    @Path("/games/{gameId}/players/{playerId}/bomb")
    @SneakyThrows
    public Response postPutBomb(@PathParam("gameId") Long gameId, @PathParam("playerId") Long playerId, MovePlayerRequest movePlayerRequest) {
        if (gameService.exists(gameId, playerId))
            return Response.status(Response.Status.NOT_FOUND).build();

        if (movePlayerRequest == null || movePlayerRequest.getPosX() == null || movePlayerRequest.getPosY() == null) {
            return Response.status(Response.Status.BAD_REQUEST).build();
        }

        Game updatedGame = gameService.putBomb(gameId, playerId, movePlayerRequest.getPosX(), movePlayerRequest.getPosY());
        if (updatedGame.getId() == null)
            return Response.status(Response.Status.BAD_REQUEST).build();
        if (updatedGame.getPlayers_id() == null)
            return Response.status(Response.Status.TOO_MANY_REQUESTS).build();
        GameDetailResponse newUpdatedDetailResponse = new GameDetailResponse().withId(updatedGame.getId()).withPlayers(updatedGame.getPlayers_id()).withMap(updatedGame.getMap()).withState(String.valueOf(updatedGame.getState())).withStartTime(updatedGame.getStarttime());
        return Response.ok(newUpdatedDetailResponse).build();
    }
}

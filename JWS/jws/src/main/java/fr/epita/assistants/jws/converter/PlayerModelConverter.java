package fr.epita.assistants.jws.converter;

import fr.epita.assistants.jws.data.model.PlayerModel;
import fr.epita.assistants.jws.domain.entity.PlayerEntity;

import javax.enterprise.context.ApplicationScoped;

@ApplicationScoped
public class PlayerModelConverter {
    public PlayerEntity convertToPlayerEntity(PlayerModel playerModel) {
        return new PlayerEntity().withId(playerModel.getId()).withLastbomb(playerModel.getLastbomb()).withLastmovement(playerModel.getLastmovement()).withLives(playerModel.getLives()).withName(playerModel.getName()).withPosX(playerModel.getPosX()).withPosY(playerModel.getPosY());
    }
}

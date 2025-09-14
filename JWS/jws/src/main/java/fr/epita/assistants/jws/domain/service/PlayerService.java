package fr.epita.assistants.jws.domain.service;

import fr.epita.assistants.jws.converter.PlayerModelConverter;
import fr.epita.assistants.jws.data.repository.PlayerRepository;
import fr.epita.assistants.jws.domain.entity.PlayerEntity;
import lombok.Getter;

import javax.inject.Inject;
import java.util.ArrayList;

@Getter
public class PlayerService {
    @Inject
    PlayerRepository playerRepository;
    @Inject
    PlayerModelConverter playerModelConverter;
    @Getter
    ArrayList<PlayerEntity> playerEntities;

    public PlayerService() {
        this.playerEntities = new ArrayList<>();
    }

    public void addPlayerEntity(PlayerEntity playerEntity) {
        this.playerEntities.add(playerEntity);
    }

    public void getGameRepository() {
        playerEntities.addAll(playerRepository.findAll().stream().map(pR -> playerModelConverter.convertToPlayerEntity(pR)).toList());
    }
}

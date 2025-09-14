package fr.epita.assistants.jws.domain.entity;

import fr.epita.assistants.jws.utils.GameState;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class GameEntity {
    private Long id;
    private java.sql.Timestamp starttime;
    private GameState state;
    private long nb_players;
}

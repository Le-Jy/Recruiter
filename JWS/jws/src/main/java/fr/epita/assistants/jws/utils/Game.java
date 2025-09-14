package fr.epita.assistants.jws.utils;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.With;

import java.util.List;
@AllArgsConstructor
@NoArgsConstructor
@With
@Getter
public class Game {
    @JsonProperty
    private Long id;
    @JsonProperty
    private java.sql.Timestamp starttime;
    @JsonProperty
    private GameState state;
    private List<String> map;
    private List<Player> players_id;
}

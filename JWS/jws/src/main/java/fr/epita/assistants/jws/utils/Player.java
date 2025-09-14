package fr.epita.assistants.jws.utils;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import lombok.With;

@AllArgsConstructor
@NoArgsConstructor
@With
public class Player {
    @JsonProperty
    private Long id;
    @JsonProperty
    private String name;
    @JsonProperty
    private int lives;
    @JsonProperty
    private int posX;
    @JsonProperty
    private int posY;
}

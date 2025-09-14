package fr.epita.assistants.jws.domain.entity;

import lombok.*;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@With
public class PlayerEntity {
    private Long id;
    private java.sql.Timestamp lastbomb;
    private java.sql.Timestamp lastmovement;
    private int lives;
    private String name;
    private int posX;
    private int posY;
}

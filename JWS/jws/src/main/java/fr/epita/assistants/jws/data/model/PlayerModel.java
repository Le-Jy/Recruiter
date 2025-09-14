package fr.epita.assistants.jws.data.model;

import io.quarkus.hibernate.orm.panache.PanacheEntity;
import io.quarkus.hibernate.orm.panache.PanacheEntityBase;
import lombok.*;

import javax.persistence.*;
import java.util.List;

@Entity
@Table(name = "player")
@Getter
@NoArgsConstructor
@With
@AllArgsConstructor
@Setter
public class PlayerModel extends PanacheEntityBase {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private java.sql.Timestamp lastbomb;

    private java.sql.Timestamp lastmovement;

    private int lives;

    private String name;

    private int posX;

    private int posY;

    private int position;

    @ManyToOne
    private GameModel gameModel;
}

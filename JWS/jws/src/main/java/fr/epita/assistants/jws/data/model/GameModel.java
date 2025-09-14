package fr.epita.assistants.jws.data.model;

import fr.epita.assistants.jws.utils.GameState;
import io.quarkus.hibernate.orm.panache.PanacheEntity;
import io.quarkus.hibernate.orm.panache.PanacheEntityBase;
import lombok.*;

import javax.persistence.*;
import java.util.List;

@Entity
@Table(name = "game")
@Getter
@AllArgsConstructor
@NoArgsConstructor
@With
@Setter
public class GameModel extends PanacheEntityBase {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    @Column(name = "startime")
    private java.sql.Timestamp starttime;
    @Column(name = "state")
    private String state;

    @ElementCollection
    @CollectionTable(name = "game_map", joinColumns = @JoinColumn(name = "gamemodel_id"))
    private List<String> map;

    @OneToMany
    @JoinTable(name = "game_player", joinColumns = @JoinColumn(name = "gamemodel_id"), inverseJoinColumns =
    @JoinColumn(name = "players_id"))
    private List<PlayerModel> players_id;
}
package fr.epita.assistants.jws.presentation.rest.response;

import fr.epita.assistants.jws.utils.Player;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.NoArgsConstructor;
import lombok.With;

import java.sql.Timestamp;
import java.util.List;
@AllArgsConstructor
@NoArgsConstructor
@With
@Builder
public class GameDetailResponse {
    public Timestamp startTime;
    public String state;
    public List<Player> players;
    public List<String> map;
    public Long id;
}

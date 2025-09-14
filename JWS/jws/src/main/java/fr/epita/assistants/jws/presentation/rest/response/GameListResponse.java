package fr.epita.assistants.jws.presentation.rest.response;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.NoArgsConstructor;
import lombok.With;

@AllArgsConstructor
@NoArgsConstructor
@With
@Builder
public class GameListResponse {
    public Long id;
    public Long players;
    public String state;
}
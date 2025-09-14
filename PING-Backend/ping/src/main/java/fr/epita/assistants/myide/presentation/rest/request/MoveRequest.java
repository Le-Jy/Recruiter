package fr.epita.assistants.myide.presentation.rest.request;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.nio.file.Path;

@Getter
@AllArgsConstructor
@NoArgsConstructor
public class MoveRequest {
    @JsonProperty("src")
    Path src;

    @JsonProperty("dst")
    Path dst;
}
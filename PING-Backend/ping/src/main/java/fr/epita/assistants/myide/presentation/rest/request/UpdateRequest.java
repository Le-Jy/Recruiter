package fr.epita.assistants.myide.presentation.rest.request;

import java.nio.file.Path;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Getter
@AllArgsConstructor
@NoArgsConstructor
public class UpdateRequest {

    @JsonProperty("path")
    Path path;

    @JsonProperty("from")
    int from;

    @JsonProperty("to")
    int to;
    
    @JsonProperty("content")
    String content;
}

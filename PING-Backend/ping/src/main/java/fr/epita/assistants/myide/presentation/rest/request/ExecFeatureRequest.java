package fr.epita.assistants.myide.presentation.rest.request;

import java.nio.file.Path;
import java.util.List;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;

@Getter
@NoArgsConstructor
@AllArgsConstructor
public class ExecFeatureRequest {
    @JsonProperty("feature")
    String feature;

    @JsonProperty("params")
    List<String> params;

    @JsonProperty("project")
    Path project;
}

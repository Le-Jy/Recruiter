package fr.epita.assistants.presentation.rest.response;


import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Getter;

@Getter
public class HelloResponse {
    @JsonProperty("content")
    String content;

    public HelloResponse(String content) {
        this.content = "hello " + content;
    }
}

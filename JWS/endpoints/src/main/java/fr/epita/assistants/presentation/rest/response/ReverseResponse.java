package fr.epita.assistants.presentation.rest.response;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.Getter;

@Getter
public class ReverseResponse {
    @JsonProperty("original")
    String original;
    @JsonProperty("reversed")
    String reversed;

    public ReverseResponse(String original) {
        this.original = original;
        this.reversed = new StringBuilder(original).reverse().toString();
    }
}

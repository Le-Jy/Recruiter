package fr.epita.assistants.practicelombok;

import lombok.*;

@AllArgsConstructor
@NoArgsConstructor
@Getter
@ToString(of = {"name", "speed"})
@EqualsAndHashCode(of = {"name", "nickname"})
public class Horse {
    @Setter private String name;
    @Setter private String nickname;
    private int speed;
}
package fr.epita.assistants.data.model;

import javax.persistence.*;
import java.util.Set;

@Entity
@Table(name = "course_model")
public class CourseModel {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "name")
    private String courseName;

    @ElementCollection
    @CollectionTable(name = "course_model_tags", joinColumns = @JoinColumn(name = "course_id"))
    @Column(name = "tag")
    private Set<String> tags;
}

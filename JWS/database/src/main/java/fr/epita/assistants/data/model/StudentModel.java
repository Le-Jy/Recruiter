package fr.epita.assistants.data.model;

import javax.persistence.*;

@Entity
@Table(name = "student_model")
public class StudentModel {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "name")
    private String studentName;

    @ManyToOne
    @JoinColumn(name = "course_id")
    private CourseModel course;
}

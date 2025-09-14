package fr.epita.assistants.myide.domain.entity.project;

import java.util.List;
import java.util.Optional;
import java.util.Set;

import javax.validation.constraints.NotNull;

import fr.epita.assistants.myide.domain.entity.Aspect;
import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;
import lombok.*;

@AllArgsConstructor
@NoArgsConstructor
@With
public class ProjectImpl implements Project {

    private Set<Aspect> aspects;
    private Node rootNode;

    @Override
    public @NotNull Set<Aspect> getAspects() {
        return aspects;
    }

    @Override
    public @NotNull Optional<Feature> getFeature(@NotNull final Feature.Type featureType) {
        List<Feature> features = this.getFeatures();
        return features.stream()
            .filter(feature -> feature.type().equals(featureType))
            .findFirst();
    }

    @Override
    public @NotNull Node getRootNode() {
        return rootNode;
    }

    public void addAspect(Aspect aspect) {
        this.aspects.add(aspect);
    }
}
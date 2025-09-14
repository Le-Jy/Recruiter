package fr.epita.assistants.myide.domain.entity.aspect;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import fr.epita.assistants.MyIde.Configuration;
import fr.epita.assistants.myide.domain.entity.Aspect;
import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.feature.any.CleanupFeature;
import fr.epita.assistants.myide.domain.entity.feature.any.DistFeature;
import fr.epita.assistants.myide.domain.entity.feature.any.SearchFeature;

public class AnyAspect implements Aspect {

    private Type type = Mandatory.Aspects.ANY;
    private final Set<Feature> features;

    public AnyAspect(Project project, Configuration configuration) throws Exception {
        this.features = new HashSet<>();
        this.features.add(new CleanupFeature());
        this.features.add(new DistFeature());
        this.features.add(new SearchFeature(project, configuration));
    }

    @Override
    public Type getType() {
        return type;
    }

    @Override
    public List<Feature> getFeatureList() {
        return new ArrayList<>(this.features);
    }
}

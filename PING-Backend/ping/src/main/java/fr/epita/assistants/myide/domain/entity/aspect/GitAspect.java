package fr.epita.assistants.myide.domain.entity.aspect;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import fr.epita.assistants.myide.domain.entity.Aspect;
import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.feature.git.AddFeature;
import fr.epita.assistants.myide.domain.entity.feature.git.CommitFeature;
import fr.epita.assistants.myide.domain.entity.feature.git.PullFeature;
import fr.epita.assistants.myide.domain.entity.feature.git.PushFeature;

public class GitAspect implements Aspect {

    private final Type type = Mandatory.Aspects.GIT;
    private Set<Feature> features;

    public GitAspect() {
        this.features = new HashSet<>();
        this.features.add(new AddFeature());
        this.features.add(new CommitFeature());
        this.features.add(new PullFeature());
        this.features.add(new PushFeature());
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
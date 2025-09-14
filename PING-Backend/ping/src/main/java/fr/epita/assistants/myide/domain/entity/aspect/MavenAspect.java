package fr.epita.assistants.myide.domain.entity.aspect;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import fr.epita.assistants.myide.domain.entity.Aspect;
import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.feature.maven.CleanFeature;
import fr.epita.assistants.myide.domain.entity.feature.maven.CompileFeature;
import fr.epita.assistants.myide.domain.entity.feature.maven.ExecFeature;
import fr.epita.assistants.myide.domain.entity.feature.maven.InstallFeature;
import fr.epita.assistants.myide.domain.entity.feature.maven.PackageFeature;
import fr.epita.assistants.myide.domain.entity.feature.maven.TestFeature;
import fr.epita.assistants.myide.domain.entity.feature.maven.TreeFeature;

public class MavenAspect implements Aspect {

    private final Type type = Mandatory.Aspects.MAVEN;
    private Set<Feature> features;

    public MavenAspect() {
        this.features = new HashSet<>();
        this.features.add(new CleanFeature());
        this.features.add(new CompileFeature());
        this.features.add(new ExecFeature());
        this.features.add(new InstallFeature());
        this.features.add(new PackageFeature());
        this.features.add(new TestFeature());
        this.features.add(new TreeFeature());
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
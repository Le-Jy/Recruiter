package fr.epita.assistants.myide.domain.entity.feature.maven;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.validation.constraints.NotNull;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.feature.ExecProcess;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class InstallFeature implements Feature {

    @Override
    public @NotNull ExecutionReport execute(Project project, Object... params) {
        List<Object> newParams = new ArrayList<>();
        newParams.add("mvn");
        newParams.add("install");
        newParams.addAll(Arrays.asList(params));

        return ExecProcess.execProcess(project, newParams.toArray());
    }

    @Override
    public @NotNull Type type() {
        return Mandatory.Features.Maven.INSTALL;
    }
}
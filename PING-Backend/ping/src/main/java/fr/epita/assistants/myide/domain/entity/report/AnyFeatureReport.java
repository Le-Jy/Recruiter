package fr.epita.assistants.myide.domain.entity.report;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;

import javax.validation.constraints.NotNull;
import java.util.List;

/**
 * @param project     The project being returned.
 * @param isSuccess     Is the report successful.
 */
public record AnyFeatureReport(@NotNull Project project, boolean isSuccess)
        implements Feature.ExecutionReport {
}
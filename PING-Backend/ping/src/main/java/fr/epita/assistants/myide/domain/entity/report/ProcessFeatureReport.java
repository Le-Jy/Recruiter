package fr.epita.assistants.myide.domain.entity.report;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Node;

import javax.validation.constraints.NotNull;
import java.util.List;

/**
 * @param processOutput All the output of the process.
 * @param isSuccess     Is the report successful.
 */
public record ProcessFeatureReport(@NotNull List<String> processOutput, boolean isSuccess)
        implements Feature.ExecutionReport {
}

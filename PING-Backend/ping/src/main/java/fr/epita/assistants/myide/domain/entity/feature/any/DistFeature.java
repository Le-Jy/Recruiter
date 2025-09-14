package fr.epita.assistants.myide.domain.entity.feature.any;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Set;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import javax.validation.constraints.NotNull;

import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.report.AnyFeatureReport;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class DistFeature implements Feature {

    private void createArchive(Node node, ZipOutputStream zos, Path parentPath) throws IOException {
        Path filePath = parentPath.relativize(node.getPath());
        if (node.isFile()) {
            zos.putNextEntry(new ZipEntry(filePath.toString()));
            Files.copy(node.getPath(), zos);
            zos.closeEntry();
        } else {
            zos.putNextEntry(new ZipEntry(filePath.toString() + "/"));
            zos.closeEntry();
            for (Node child : node.getChildren()) {
                createArchive(child, zos, parentPath);
            }
        }
    }

    @Override
    public @NotNull ExecutionReport execute(Project project, Object... params) {

        File myideignore = RemoveTrashFiles.getMyIdeIgnore(project);

        Path zipFile = project.getRootNode().getPath()
                .resolveSibling(Paths.get(project.getRootNode().getPath().getFileName().toString() + ".zip"));

        try {
            if (myideignore != null) {
                Set<String> trashFiles = RemoveTrashFiles.getTrashFiles(myideignore);

                if (trashFiles == null) {
                    return new AnyFeatureReport(project, false);
                }

                RemoveTrashFiles.removeTrashFiles(project.getRootNode(), trashFiles);
            }
            try (ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(zipFile.toFile()))) {
                // for (Node child : project.getRootNode().getChildren()) {

                createArchive(project.getRootNode(), zos, project.getRootNode().getPath().getParent());
                // }
            }

        } catch (Exception e) {
            return new AnyFeatureReport(project, false);
        }
        return new AnyFeatureReport(project, true);
    }

    @Override
    public @NotNull Type type() {
        return Mandatory.Features.Any.DIST;
    }

}
package fr.epita.assistants.myide.domain.entity.feature;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import fr.epita.assistants.myide.domain.entity.Feature.ExecutionReport;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.report.ProcessFeatureReport;

/*
 * Used to exec process builders (Git or Maven features)
 */
public class ExecProcess {
    public static ExecutionReport execProcess(Project project, Object... params)     {

        ProcessBuilder processBuilder = new ProcessBuilder();
        List<String> command = new ArrayList<>();
        for (Object param : params) {
            command.add(param.toString());
        }

        processBuilder.command(command);

        processBuilder.directory(project.getRootNode().getPath().toFile());

        try {
            Process process = processBuilder.start();
            int code = process.waitFor();
            List<String> rapport = new ArrayList<String>();

            if (code != 0) {
                try (BufferedReader br = new BufferedReader(new InputStreamReader(process.getErrorStream()))) {
                    String line;
                    while ((line = br.readLine()) != null) {
                        rapport.add(line);
                    }
                }

                return new ProcessFeatureReport(rapport, false);
            }

            try (BufferedReader br = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
                String line;
                while ((line = br.readLine()) != null) {
                    rapport.add(line);
                }
            }

            return new ProcessFeatureReport(rapport, true);

        } catch (Exception e) {
            return () -> false;
        }
    }
}

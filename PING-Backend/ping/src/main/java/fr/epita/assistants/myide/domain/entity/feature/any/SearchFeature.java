package fr.epita.assistants.myide.domain.entity.feature.any;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import javax.validation.constraints.NotNull;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.StringField;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.store.ByteBuffersDirectory;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;

import fr.epita.assistants.MyIde.Configuration;
import fr.epita.assistants.myide.domain.entity.Feature;
import fr.epita.assistants.myide.domain.entity.Mandatory;
import fr.epita.assistants.myide.domain.entity.Node;
import fr.epita.assistants.myide.domain.entity.Project;
import fr.epita.assistants.myide.domain.entity.node.NodeImpl;
import fr.epita.assistants.myide.domain.entity.report.SearchFeatureReport;

public class SearchFeature implements Feature {

    private Configuration configuration;
    private Directory directory = null;

    public SearchFeature(Project project, Configuration configuration) throws Exception {
        this.configuration = configuration;
    }

    public void updateSearch(Project project) throws Exception {
        Analyzer analyzer = new StandardAnalyzer();
        if (configuration == null) {
            directory = new ByteBuffersDirectory();
        } else {
            directory = FSDirectory.open(configuration.tempFolder());
        }
        IndexWriterConfig config = new IndexWriterConfig(analyzer);
        IndexWriter iwriter = new IndexWriter(directory, config);

        indexFiles(project.getRootNode(), iwriter);
        iwriter.close();
    }

    private void indexFiles(Node node, IndexWriter iwriter) throws Exception {
        if (node.isFile()) {
            Document doc = new Document();
            FileReader fileReader = new FileReader(node.getPath().toFile());
            doc.add(new StringField("node", node.getPath().toString(), Field.Store.YES));
            doc.add(new TextField("text", fileReader));
            iwriter.addDocument(doc);
        } else {
            for (Node child : node.getChildren()) {
                indexFiles(child, iwriter);
            }
        }
    }

    @Override
    public @NotNull ExecutionReport execute(Project project, Object... params) {
        if (params.length != 1) {
            return new SearchFeatureReport(null, false);
        }

        try {
            if (directory != null) {
                directory.close();
            }
            updateSearch(project);
            List<String> results = search(params[0].toString());
            if (results.isEmpty()) {
                return new SearchFeatureReport(null, false);
            }
            List<Node> resultNodes = new ArrayList<>();
            for (String path : results) {
                resultNodes.add(new NodeImpl(Paths.get(path), Node.Types.FILE));
            }

            return new SearchFeatureReport(resultNodes, true);
        } catch (Exception e) {
            return new SearchFeatureReport(null, false);
        }
    }

    private List<String> search(String searchQuery) throws Exception {

        Analyzer analyzer = new StandardAnalyzer();

        DirectoryReader ireader = DirectoryReader.open(directory);
        IndexSearcher isearcher = new IndexSearcher(ireader);

        QueryParser parser = new QueryParser("text", analyzer);
        Query query = parser.parse(searchQuery);

        ScoreDoc[] hits = isearcher.search(query, 100).scoreDocs;
        List<String> nodes = new ArrayList<>();
        for (int i = 0; i < hits.length; i++) {
            Document hitDoc = isearcher.doc(hits[i].doc);
            nodes.add(hitDoc.get("node"));
        }

        ireader.close();

        return nodes;
    }

    @Override
    public @NotNull Type type() {
        return Mandatory.Features.Any.SEARCH;
    }
}
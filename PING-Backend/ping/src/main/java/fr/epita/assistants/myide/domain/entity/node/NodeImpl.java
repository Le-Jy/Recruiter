package fr.epita.assistants.myide.domain.entity.node;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import javax.validation.constraints.NotNull;

import fr.epita.assistants.myide.domain.entity.Node;

public class NodeImpl implements Node {

    private Path path;
    private Type type;
    private List<Node> childrens;

    public NodeImpl(Path path, Node.Type type)
    {
        this.path = path;
        this.type = type;
        this.childrens = new ArrayList<>();
    }

    @Override
    public @NotNull Path getPath() {
        return this.path;
    }

    @Override
    public @NotNull Type getType() {
        return this.type;
    }

    @Override
    public @NotNull List<Node> getChildren() {
        return childrens;
    }

    @Override
    public void addChildren(Node newNode)
    {
        this.childrens.add(newNode);
    }

    @Override
    public void removeChildren(Node node) {
        this.childrens.remove(node);
    }

    @Override
    public String toString() {
        String res = this.type.toString() + " : " + this.path.toString() + "\n";
        for (Node child : this.childrens) {
            res += child.toString();
        }

        return res;
    }
}

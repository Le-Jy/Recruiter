package fr.epita.assistants.myebook;

public interface IEditable {
    // Overwrite the contents of the current page.
    void writeCurrentPage(String pageText);
    // Add a new page after the one being read.
    void addPage();
    // Delete the current page.
    void deletePage();
}

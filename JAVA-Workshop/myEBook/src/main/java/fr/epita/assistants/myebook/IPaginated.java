package fr.epita.assistants.myebook;

public interface IPaginated {
    // This should make the object opened to a specific page.
    // Page indices start at 0.
    // If the page number is invalid, do nothing.
    void openToPage(int page);

    // This method returns the currently opened page.
    int getCurrentPage();

    // This method returns the total number of pages in the object.
    int getPageCount();
}
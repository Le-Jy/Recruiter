package fr.epita.assistants.myebook;

import java.util.ArrayList;
import java.util.List;

public class EBook extends EBookReader implements IEditable, IPaginated{
    int currentPage;
    int pageCount;
    String name;
    List<String> pages;

    public EBook(String name) {
        this.name = name;
        this.pages = new ArrayList<String>();
        this.addPage();
    }

    // Get the name of the book.
    public String getName() {
        return this.name;
    }
    // Create a book from the EBook.
    // The instantiated book is a version of the ebook, and can no longer be modified
    public Book print() {
        return new Book(this.name, this.pages);
    }

    public void writeCurrentPage(String pageText) {
        if (this.pageCount == 0)
            this.addPage();
        this.pages.set(this.currentPage, this.pages.get(this.currentPage).concat(pageText));
    }

    public void addPage() {
        if (this.pageCount == 0)
            this.pages.add("");
        else
            this.pages.add(this.currentPage + 1, "");
        this.pageCount++;
    }

    public void deletePage() {
        if (this.currentPage < 0)
            return;
        if (this.pageCount == 1) {
            this.pages.clear();
            this.pages.add("");
        }
        else {
            this.pages.remove(this.currentPage);
            this.pageCount--;
        }
    }

    public void openToPage(int page) {
        if (page >= 0 && page < this.pageCount)
            this.currentPage = page;
    }

    public int getCurrentPage() {
        return currentPage;
    }

    public int getPageCount() {
        return pageCount;
    }
}

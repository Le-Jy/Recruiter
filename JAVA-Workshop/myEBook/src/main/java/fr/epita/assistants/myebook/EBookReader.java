package fr.epita.assistants.myebook;

import java.util.ArrayList;
import java.util.List;
public class EBookReader implements IReadable, IPaginated, IUpdatable{
    String name;
    int pageCount;
    int currentPage;
    List<String> pages;
    double version;
    // Instantiate a new ebook reader with firmware 1.0
    public EBookReader() {
        this.version = 1.0;
    }
    // Load an ebook into the reader.
    public void openEbook(EBook ebook) {
        this.version = ebook.getVersion();
        this.name = ebook.getName();
        this.currentPage = ebook.getCurrentPage();
        this.pages = new ArrayList<String>();
        this.pages.addAll(ebook.pages);
        this.pageCount = ebook.pageCount;
    }
    public void openToPage(int page) {
        if (page >= 0 && page < this.pageCount)
            this.currentPage = page;
    }

    public int getCurrentPage() {
        if (this.name == null)
            return -1;
        return this.currentPage;
    }

    public int getPageCount() {
        if (this.name == null)
            return -1;
        return  this.pageCount;
    }

    public String readCurrentPage() {
        if (this.pageCount != 0)
            return String.valueOf(this.pages.get(this.currentPage));
        return null;
    }

    public double getVersion() {
        return this.version;
    }

    public void update(double version) {
        if (version > this.version)
            this.version = version;
    }
}

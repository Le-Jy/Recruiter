package fr.epita.assistants.myebook;

import java.util.ArrayList;
import java.util.List;

class Book extends EBook implements IPaginated, IReadable {

    int currentPage;
    final int pageCount;
    final String name;
    final List<String> pages;
    public void openToPage(int page) {
        if (page >= 0 && page < this.pageCount)
            this.currentPage = page;
    }

    public int getCurrentPage() {
        return this.currentPage;
    }

    public int getPageCount() {
        return this.pageCount;
    }

    public String readCurrentPage() {
        if (this.pageCount != 0)
            return String.valueOf(this.pages.get(this.currentPage));
        return null;
    }
    // Instantiate a book with a certain title and page contents.
    // Only the EBook class should be able to call the Book constructor since it
    // is the only one able to print it, hence it must not be public.
    Book(String name, List<String> pages){
        super(name);
        this.name = name;
        this.pages = new ArrayList<String>();
        this.pages.addAll(pages);
        this.currentPage = 0;
        this.pageCount = pages.size();
    }
    // Get the name of the book.
    public String getName() {
        return this.name;
    }

    // Create an EBook from the book.
    public EBook scan() {
        EBook result = new EBook(this.name);
        result.pages = new ArrayList<String>();
        result.pages.addAll(this.pages);
        result.pageCount = pageCount;
        result.currentPage = 0;
        return result;
    }

}

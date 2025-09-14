package fr.epita.assistants.pizzastreams;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import fr.epita.assistants.pizzastreams.Topping.*;

public class PizzaStreams {
    /**
     * @return The sum of the prices of all the pizzas in the stream
     */
    public static Integer getTotalPrice(Stream<Pizza> pizzaStream) {
        return pizzaStream.mapToInt(Pizza::getPrice).sum();
    }

    /**
     * @return The average price of the pizzas in the stream, or the
     * double NaN if the stream is empty
     */
    public static Double getAveragePrice(Stream<Pizza> pizzaStream) {
        return pizzaStream.mapToDouble(Pizza::getPrice).average().orElse(Double.NaN);
    }

    /**
     * @return Names of the pizzas, sorted by price in ascending order
     */
    public static List<String> sortByPrice(Stream<Pizza> pizzaStream) {
        return pizzaStream.sorted((P, P2) -> P.getPrice().compareTo(P2.getPrice())).map(Pizza::getName).collect(Collectors.toList());
    }

    /**
     * @return The Pizza object that has the lowest price, or null by default
     */
    public static Pizza getCheapest(Stream<Pizza> pizzaStream) {
        return pizzaStream.sorted((P, P2) -> P.getPrice().compareTo(P2.getPrice())).reduce((first, second) -> first).orElse(null);
    }

    /**
     * @return Names of the pizzas with meat (Protein)
     */
    public static List<String> getCarnivorous(Stream<Pizza> pizzaStream) {
        return pizzaStream.filter(P ->
                P.getTopping().getProtein().isPresent()
        ).map(Pizza::getName).collect(Collectors.toList());
    }

    /**
     * @return Names of the pizzas with at least one Vegetable and no Proteins
     */
    public static List<String> getVeggies(Stream<Pizza> pizzaStream) {
        return pizzaStream.filter(P ->
                P.getTopping().getProtein().isEmpty() && !P.getTopping().getVegetableList().isEmpty()
        ).map(Pizza::getName).collect(Collectors.toList());
    }

    /**
     * @return true if all the pizzas with a nature dough are based with tomato
     * and mozzarella (italian pizza criteria), false otherwise
     */
    public static boolean areAllNatureItalians(Stream<Pizza> pizzaStream) {
        return pizzaStream.filter(P -> P.getDough().equals(Dough.NATURE)).allMatch(P -> P.getDough().equals(Dough.NATURE) && P.getTopping().getSauce().equals(Sauce.TOMATO) && P.getTopping().getCheese().equals(Cheese.MOZZARELLA));
    }
}

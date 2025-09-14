package fr.epita.assistants.travel;

import com.opencsv.CSVReader;
import com.opencsv.CSVReaderBuilder;
import java.util.List;

import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Country {
    String countryName;
    String countryZone;

    public Map<String, Integer> travelTimes;

    public Country(String countryName, String countryZone, String inputFilePath) throws IOException {
        this.countryName = countryName;
        this.countryZone = countryZone;
        this.travelTimes = initTravelTimes(inputFilePath);
    }
    public Map<String, Integer> initTravelTimes(String inputFilePath) throws IOException {
        Map<String, Integer> result = new HashMap<String, Integer>();
        FileReader fileReader = new FileReader(inputFilePath);
        CSVReader csvReader = new CSVReaderBuilder(fileReader).withSkipLines(1).build();
        List<String[]> allData = csvReader.readAll();
        for (String[] row : allData) {
                if (row[0].equals(this.countryName))
                {
                    result.put(row[1], Integer.parseInt(row[2]));
                }
                if ((row[1].equals(this.countryName))) {
                    result.put(row[0], Integer.parseInt(row[2]));
                }
        }
        return result;
    }
}

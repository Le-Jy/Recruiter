package fr.epita.assistants.ministreamsmusic.dataaccess;

import fr.epita.assistants.ministreamsmusic.data.Song;
import fr.epita.assistants.ministreamsmusic.data.Artist;

import java.util.List;
import java.util.stream.Collectors;

public class StreamsSongs {
    public static List<String> getOlderArtists(List<Song> songs) {
        return songs.stream()
                .filter(song -> song.getArtist().getAge() >= 30)
                .map(song -> song.getArtist().getSurname())
                .distinct()
                .limit(10)
                .collect(Collectors.toList());
    }

    public static Integer getSumAges(List<Song> songs) {
        return songs.stream()
                .map(Song::getArtist)
                .filter(artist -> artist.getAge() >= 20)
                .mapToInt(Artist::getAge)
                .sum();
    }

    public static List<String> getMusics(List<Song> songs) {
        return songs.stream()
                .filter(song -> song.getArtist().getName().toLowerCase().contains("an"))
                .map(Song::getName)
                .limit(10)
                .collect(Collectors.toList());
    }
}

package fr.epita.assistants.seq;

import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.*;
import java.util.stream.*;
@FunctionalInterface
public interface Seq<T> extends ExtendedStream<T>{

    Stream<T> impl();
    static <T> Seq<T> of(List<T> values) {
        return values::stream;
    }
    static <T> Seq<T> of(T... values) {
        return Seq.of(Arrays.stream(values).toList());
    }
    static <T> Seq<T> of(Stream<T> values) {
        return Seq.of(values.toList());
    }
    @Override
    default <KEY_TYPE> Map<KEY_TYPE, T> toMap(final Function<T, KEY_TYPE> keyMapper) {
        Map<KEY_TYPE,T> res = new HashMap<>();
        impl().forEach(e -> res.put(keyMapper.apply(e), e));
        return res;
    }

    @Override
    default <KEY_TYPE, VALUE_TYPE, MAP_TYPE extends Map<KEY_TYPE, VALUE_TYPE>> MAP_TYPE toMap(final MAP_TYPE map, final Function<T, KEY_TYPE> keyMapper, final Function<T, VALUE_TYPE> valueMapper) {
        Map<KEY_TYPE, VALUE_TYPE> res = toMap(keyMapper, valueMapper);
        map.putAll(res);
        return map;
    }

    @Override
    default <KEY_TYPE, VALUE_TYPE> Map<KEY_TYPE, VALUE_TYPE> toMap(final Function<T, KEY_TYPE> keyMapper, final Function<T, VALUE_TYPE> valueMapper) {
        Map<KEY_TYPE, VALUE_TYPE> res = new HashMap<>();
        impl().forEach(e -> res.put(keyMapper.apply(e), valueMapper.apply(e)));
        return res;
    }

    @Override
    default List<T> toList() {
        return impl().toList();
    }

    @Override
    default <LIST extends List<T>> LIST toList(final LIST list) {
        list.addAll(impl().toList());
        return list;
    }

    @Override
    default Set<T> toSet() {
        return impl().collect(Collectors.toSet());
    }

    @Override
    default <SET extends Set<T>> SET toSet(final SET set) {
        set.addAll(impl().collect(Collectors.toSet()));
        return set;
    }

    @Override
    default <ASSOCIATED_TYPE> ExtendedStream<Pair<T, ASSOCIATED_TYPE>> associate(final Supplier<ASSOCIATED_TYPE> supplier) {
        return Seq.of(impl().map(e -> new Pair<>(e, supplier.get())));
    }

    @Override
    default <ASSOCIATED_TYPE> ExtendedStream<Pair<T, ASSOCIATED_TYPE>> associate(final Stream<ASSOCIATED_TYPE> supplier) {
        AtomicInteger i = new AtomicInteger();
        var sup = supplier.toList();
        return Seq.of(impl().map(e -> new Pair<>(e , sup.get(i.getAndIncrement()))));
    }

    @Override
    default ExtendedStream<T> print() {
        impl().forEach(System.out::println);
        return  of(impl());
    }

    @Override
    default ExtendedStream<T> plus(final Stream<T> stream) {
        return of(Stream.concat(impl(), stream));
    }

    @Override
    default String join(final String delimiter) {
        var l = new ArrayList<>(impl().toList());
        StringBuilder res = new StringBuilder(String.valueOf(l.get(0)));
        l.remove(0);
        l.forEach(e -> res.append(delimiter).append(e));
        return String.valueOf(res);
    }

    @Override
    default String join() {
        var l = new ArrayList<>(impl().toList());
        StringBuilder res = new StringBuilder(String.valueOf(l.get(0)));
        l.remove(0);
        l.forEach(res::append);
        return String.valueOf(res);
    }

    @Override
    default <KEY_TYPE> ExtendedStream<Pair<KEY_TYPE, ExtendedStream<T>>> partition(final Function<T, KEY_TYPE> pivot) {
        var tmp = impl().collect(Collectors.groupingBy(pivot));
        List<Pair<KEY_TYPE, ExtendedStream<T>>> l = new ArrayList<>();
        tmp.forEach((K,Q) -> l.add(new Pair<>(K, Seq.of(Q))));
        return Seq.of(l);
    }

    @Override
    default Stream<T> filter(Predicate<? super T> predicate) {
        return impl().filter(predicate);
    }

    @Override
    default <R> Stream<R> map(Function<? super T, ? extends R> mapper) {
        return impl().map(mapper);
    }

    @Override
    default IntStream mapToInt(ToIntFunction<? super T> mapper) {
        return impl().mapToInt(mapper);
    }

    @Override
    default LongStream mapToLong(ToLongFunction<? super T> mapper) {
        return impl().mapToLong(mapper);
    }

    @Override
    default DoubleStream mapToDouble(ToDoubleFunction<? super T> mapper) {
        return impl().mapToDouble(mapper);
    }

    @Override
    default <R> Stream<R> flatMap(Function<? super T, ? extends Stream<? extends R>> mapper) {
        return impl().flatMap(mapper);
    }

    @Override
    default IntStream flatMapToInt(Function<? super T, ? extends IntStream> mapper) {
        return impl().flatMapToInt(mapper);
    }

    @Override
    default LongStream flatMapToLong(Function<? super T, ? extends LongStream> mapper) {
        return impl().flatMapToLong(mapper);
    }

    @Override
    default DoubleStream flatMapToDouble(Function<? super T, ? extends DoubleStream> mapper) {
        return impl().flatMapToDouble(mapper);
    }

    @Override
    default Stream<T> distinct() {
        return impl().distinct();
    }

    @Override
    default Stream<T> sorted() {
        return impl().sorted();
    }

    @Override
    default Stream<T> sorted(Comparator<? super T> comparator) {
        return impl().sorted();
    }

    @Override
    default Stream<T> peek(Consumer<? super T> action) {
        return impl().peek(action);
    }

    @Override
    default Stream<T> limit(long maxSize) {
        return impl().limit(maxSize);
    }

    @Override
    default Stream<T> skip(long n) {
        return impl().skip(n);
    }

    @Override
    default void forEach(Consumer<? super T> action) {
        impl().forEach(action);
    }

    @Override
    default void forEachOrdered(Consumer<? super T> action) {
        impl().forEachOrdered(action);
    }

    @Override
    default Object[] toArray() {
        return impl().toArray();
    }

    @Override
    default <A> A[] toArray(IntFunction<A[]> generator) {
        return impl().toArray(generator);
    }

    @Override
    default T reduce(T identity, BinaryOperator<T> accumulator) {
        return impl().reduce(identity, accumulator);
    }

    @Override
    default Optional<T> reduce(BinaryOperator<T> accumulator) {
        return impl().reduce(accumulator);
    }

    @Override
    default <U> U reduce(U identity, BiFunction<U, ? super T, U> accumulator, BinaryOperator<U> combiner) {
        return impl().reduce(identity, accumulator, combiner);
    }

    @Override
    default <R> R collect(Supplier<R> supplier, BiConsumer<R, ? super T> accumulator, BiConsumer<R, R> combiner) {
        return impl().collect(supplier, accumulator, combiner);
    }

    @Override
    default <R, A> R collect(Collector<? super T, A, R> collector) {
        return impl().collect(collector);
    }

    @Override
    default Optional<T> min(Comparator<? super T> comparator) {
        return impl().min(comparator);
    }

    @Override
    default Optional<T> max(Comparator<? super T> comparator) {
        return impl().max(comparator);
    }

    @Override
    default long count() {
        return impl().count();
    }

    @Override
    default boolean anyMatch(Predicate<? super T> predicate) {
        return impl().anyMatch(predicate);
    }

    @Override
    default boolean allMatch(Predicate<? super T> predicate) {
        return impl().allMatch(predicate);
    }

    @Override
    default boolean noneMatch(Predicate<? super T> predicate) {
        return impl().noneMatch(predicate);
    }

    @Override
    default Optional<T> findFirst() {
        return impl().findFirst();
    }

    @Override
    default Optional<T> findAny() {
        return impl().findAny();
    }

    @Override
    default Iterator<T> iterator() {
        return impl().iterator();
    }

    @Override
    default Spliterator<T> spliterator() {
        return impl().spliterator();
    }

    @Override
    default boolean isParallel() {
        return impl().isParallel();
    }

    @Override
    default Stream<T> sequential() {
        return impl().sequential();
    }

    @Override
    default Stream<T> parallel() {
        return impl().parallel();
    }

    @Override
    default Stream<T> unordered() {
        return impl().unordered();
    }

    @Override
    default Stream<T> onClose(Runnable closeHandler) {
        return impl().onClose(closeHandler);
    }

    @Override
    default void close() {
        impl().close();
    }
}

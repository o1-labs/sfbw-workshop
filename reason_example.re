let someNumbers = [1, 2, 3];

let otherNumbers : list(int) = [4, 5, 6];

let anArrayOfStrings : array(string) = [| "hello", "world" |];

for (i in 0 to Array.length(anArrayOfStrings) - 1) {
    let s = anArrayOfStrings[i];
    Printf.printf("%s has length %d\n", s, String.length(s));
}

/* Alternatively, using the iter function */
Array.iter((s) => {
    Printf.printf("%s has length %d\n", s, String.length(s));
}, anArrayOfStrings);

/* Refs */

/* Variables are immutable. To create a mutable reference one writes */
let sum = ref(0); // x is initialized to 0

let anArrayOfNumbers = Array.of_list(someNumbers);
for (i in 0 to Array.length(anArrayOfStrings) - 1) {
    sum := sum^ + anArrayOfNumbers[i];
}

Printf.printf("sum is %d\n", sum^);

/* Array fold */
let sumTheFunctionalWay = Array.fold_left((+), 0, anArrayOfNumbers);
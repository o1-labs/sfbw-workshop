/* If autocomplete and typechecking is not working, run 

  npm install && npm run build
*/

module Universe = (val Snarky_universe.default ());

open! Universe.Impl;
open! Universe;

module Witness = Field;

let input = InputSpec.[(module Hash)];

/* Let's say field element is "special" if it is either
  - A perfect square and less than 2^32 and even.
  - Not a perfect square and less than 256 = 2^8
*/

/* Try hovering over "Bool" to see what functions are available in the "Bool"
  module.

  Some functions in there you might find useful:
  Bool.any
  Bool.all
  Bool.negate
  Bool.assertTrue */
module Foo = Bool

/* Try the same for "Field". */
module Bar = Field

let assertSpecial = (x) => {
  /* This implicitly asserts that x fits in 32 bits, which means it's < 2^32. */
  let bits = Field.toBits(~length=32, x);

  /* Hint: Array.sub lets you get a slice of an array, and Array.to_list turns an
  array into a list */
  let fitsIn8Bits = failwith("TODO");

  failwith("TODO");
};

/* Proves that we know a preimage to the given hash which is special */
let main = (preimage: Witness.t, h, ()) => {
  /* TODO: Check that "preimage" hashes to "h" */

  assertSpecial(preimage);
};

runMain(input, (module Witness), main);

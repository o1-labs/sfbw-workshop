/* If autocomplete and typechecking is not working, run 

  npm install && npm run build
*/

module Universe = (val Snarky_universe.default());
open! Universe.Impl;
open! Universe;

/* This SNARK will prove membership 32 elements back in a hash chain.

See [here](https://upload.wikimedia.org/wikipedia/commons/thumb/8/8c/Hashlink_timestamping.svg/600px-Hashlink_timestamping.svg.png)
for an image of a hash chain */

/* Our witness is a list of hashes */
module Witness = {
  let length = 32;

  type t = array(Hash.t);

  module Constant = {
    [@deriving yojson]
    type t = array(Hash.Constant.t);
  };

  /* This "typ" is just a value representing the type of the witness. */
  let typ = Typ.array(~length, Hash.typ);
};

/* Our statement consists of two field elements:
   1. The root hash of a merkle list/hash chain.
   2. The field element which is "buried" 32 elements back in the merkle list. */
let statement = InputSpec.[(module Hash), (module Field)];

/* Proves that there is a path [|hn, ..., h1|] such that
   hash (h1, hash(h2, hash(h3, ..., hash(hn, x) ... ))) = supposedRoot */
let main = (path: Witness.t, supposedRoot, x, ()) => {
  /* TODO: Compute the root of the hash chain implied by "x" and "path" */
  Hash.assertEqual(failwith("TODO"), supposedRoot);
};

runMain(statement, (module Witness), main);

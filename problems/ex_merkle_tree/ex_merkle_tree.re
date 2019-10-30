module Universe = (val Snarky_universe.default());
open! Universe.Impl;
open! Universe;

/* If you're not familiar with Merkle trees, you may find this
image and article helpful: https://en.wikipedia.org/wiki/Merkle_tree#/media/File:Hash_Tree.svg  */

/* We'll deal with a depth 8 merkle tree */
let depth = 8;

module Witness = {
  /* Merkle membership proof:
  - an array of bools giving the address of the element
  - the array of hashes hanging off the path to that element
  */
  type t = (array(Bool.t), array(Hash.t));

  module Constant = {
    [@deriving yojson]
    type t = (int, array(Hash.Constant.t));
  };

  let typ =
    Typ.tuple2(MerkleTree.Index.typ(~depth), MerkleTree.Path.typ(~depth));
};

let statement = InputSpec.[(module Hash), (module Field)];

/* "Field.select" is like a ternary operator on field elements */
let _three = Field.select(Bool.true_, Field.ofInt(3), Field.ofInt(97));
let _ninetySeven = Field.select(Bool.false_, Field.ofInt(3), Field.ofInt(97));

/* Hash.select is the same, but for hashes. You may find it useful in this exercise. */

let main = ((index, path): Witness.t, supposed_root, elt, ()) => {
  /* TODO: Compute the root of the merkle tree implied by the element, index, and path. */
  Hash.assertEqual(failwith("TODO"), supposed_root);
};

runMain(statement, (module Witness), main);

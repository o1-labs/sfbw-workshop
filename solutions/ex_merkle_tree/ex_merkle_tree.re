module Universe = (val Snarky_universe.default());
open! Universe.Impl;
open! Universe;

/* We'll deal with a depth 8 merkle tree */
let depth = 8;

module Witness = {
  type t = (array(Bool.t), array(Hash.t));

  module Constant = {
    [@deriving yojson]
    type t = (int, array(Hash.Constant.t));
  };

  let typ =
    Typ.tuple2(MerkleTree.Index.typ(~depth), MerkleTree.Path.typ(~depth));
};

let statement = InputSpec.[(module Hash), (module Field)];

let main = ((index, path): Witness.t, supposed_root, elt, ()) => {
  let acc = ref(elt);
  for (i in 0 to depth - 1) {
    let bit = index[i];
    let left = Hash.select(bit, path[i], acc^);
    let right = Hash.select(bit, acc^, path[i]);
    acc := Hash.hash([|left, right|]);
  };
  Hash.assertEqual(acc^, supposed_root);
};

let mainUsingBuiltIn = ((index, path): Witness.t, supposed_root, elt, ()) => {
  Bool.assertTrue(
    MerkleTree.MembershipProof.check({ index, path }, supposed_root, elt) );
};

runMain(statement, (module Witness), main);

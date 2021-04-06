/***
 * Bitwuzla: Satisfiability Modulo Theories (SMT) solver.
 *
 * This file is part of Bitwuzla.
 *
 * Copyright (C) 2007-2021 by the authors listed in the AUTHORS file.
 *
 * See COPYING for more information on using this software.
 */

#ifndef BITWUZLA_H_INCLUDED
#define BITWUZLA_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* -------------------------------------------------------------------------- */

#if __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------- */

/** The base for strings representing bit-vector values. */
enum BitwuzlaBVBase
{
  BITWUZLA_BV_BASE_BIN, ///< binary
  BITWUZLA_BV_BASE_DEC, ///< decimal
  BITWUZLA_BV_BASE_HEX, ///< hexadecimal
};
#ifndef DOXYGEN_SKIP
typedef enum BitwuzlaBVBase BitwuzlaBVBase;
#endif

/** The options supported by Bitwuzla. */
enum BitwuzlaOption
{
  /*! **Incremental solving.**
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   *
   * @note Enabling this option turns off some optimization techniques.
   * @note Enabling/disabling incremental solving after bitwuzla_check_sat()
   *       has been called is not supported.
   * @note This option cannot be enabled in combination with
   *       ::BITWUZLA_OPT_UCOPT.
   */
  BITWUZLA_OPT_INCREMENTAL,

  /*! **Model generation.**
   *
   * Values:
   *  * **1**: enable, generate model for assertions only
   *  * **2**: enable, generate model for all created terms
   *  * **0**: disable [**default**]
   *
   * @note This option cannot be enabled in combination with
   *       ::BITWUZLA_OPT_UCOPT.
   */
  BITWUZLA_OPT_PRODUCE_MODELS,

  /*! **Configure input file format.**
   *
   * If unspecified, Bitwuzla will autodetect the input file format.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_INPUT_FORMAT,

  /*! **Configure output number format for bit-vector values.**
   *
   * If unspecified, Bitwuzla will use binary representation.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_OUTPUT_NUMBER_FORMAT,

  /*! **Configure output number format for bit-vector values.**
   *
   * If unspecified, Bitwuzla will use BTOR format.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_OUTPUT_FORMAT,

  /*! **Configure the solver engine.**
   *
   * Values: TODO
   */
  BITWUZLA_OPT_ENGINE,

  /*! **Configure the SAT solver engine.**
   *
   * Values: TODO
   */
  BITWUZLA_OPT_SAT_ENGINE,

  /*! **Pretty printing.**
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_PRETTY_PRINT,

  /*! **Use non-zero exit codes for sat and unsat results.**
   *
   * When enabled, use Bitwuzla exit codes:
   * * ::BITWUZLA_SAT
   * * ::BITWUZLA_UNSAT
   * * ::BITWUZLA_UNKNOWN
   *
   * When disabled, return 0 on success (sat, unsat, unknown), and a non-zero
   * exit code for any other case.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_EXIT_CODES,

  /*! **Seed for random number generator.**
   *
   * Values:
   *  * An unsigned integer value (**default**: 0).
   */
  BITWUZLA_OPT_SEED,

  /*! **Verbosity level.**
   *
   * Values:
   *  * An unsigned integer value <= 4 (**default**: 0).
   */
  BITWUZLA_OPT_VERBOSITY,

  /*! **Log level.**
   *
   * Values:
   *  * An unsigned integer value (**default**: 0).
   */
  BITWUZLA_OPT_LOGLEVEL,

  /*! **Rewrite level.**
   *
   * Values:
   * * **0**: no rewriting
   * * **1**: term level rewriting
   * * **2**: term level rewriting and basic preprocessing
   * * **3**: term level rewriting and full preprocessing [**default**]
   *
   * @note Configuring the rewrite level after terms have been created
   *       is not allowed.
   */
  BITWUZLA_OPT_REWRITE_LEVEL,

  /*! **Boolean skeleton preprocessing.**
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_SKELETON_PREPROC,

  /*! **Ackermannization.**
   *
   * Eager addition of Ackermann constraints for function applications.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_ACKERMANN,

  /*! **Beta reduction.**
   *
   * Eager elimination of lambda terms via beta reduction.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_BETA_REDUCE,

  /*! **Eliminate ITEs.**
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_ELIMINATE_ITES,

  /*! **Eliminate bit-vector extracts.**
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_ELIMINATE_SLICES,

  /*! **Variable substitution preprocessing.**
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_VAR_SUBST,

  /*! **Unconstrained optimization.**
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_UCOPT,

  /*! **Merge lambda terms.**
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_MERGE_LAMBDAS,

  /*! **Extract lambdas.**
   *
   * Extraction of common array patterns as lambda terms.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_EXTRACT_LAMBDAS,

  /*! **Normalize bit-vector operations.**
   *
   * Normalize bit-vector addition, multiplication and bit-wise and.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_NORMALIZE,

  /*! **Normalize bit-vector addition.**
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_NORMALIZE_ADD,

  /*! **Function solver engine:
   *    Propagation-based local search sequential portfolio.**
   *
   * When function solver engine is enabled, configure propagation-based local
   * search solver engine as preprocessing step within sequential portfolio
   * setting.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_FUN_PREPROP,

  /*! **Function solver engine:
   *    Stochastic local search sequential portfolio.**
   *
   * When function solver engine is enabled, configure stochastic local
   * search solver engine as preprocessing step within sequential portfolio
   * setting.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_FUN_PRESLS,

  /*! **Function solver engine:
   *    Dual propagation optimization.**
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_FUN_DUAL_PROP,

  /*! **Function solver engine:
   *    Assumption order for dual propagation optimization.**
   *
   * Set order in which inputs are assumed in the dual propagation clone.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_FUN_DUAL_PROP_QSORT,

  /*! **Function solver engine:
   *    Justification optimization.**
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_FUN_JUST,

  /*! **Function solver engine:
   *    Justification optimization heuristic.**
   *
   * Configure heuristic to determine path selection for justification
   * optimization.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_FUN_JUST_HEURISTIC,

  /*! **Function solver engine:
   *    Lazy synthesis.**
   *
   * Configure lazy synthesis (to bit-level) of bit-vector expressions.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_FUN_LAZY_SYNTHESIZE,

  /*! **Function solver engine:
   *    Eager lemmas.**
   *
   * Configure mode for eager lemma generation.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_FUN_EAGER_LEMMAS,

  /*! **Function solver engine:
   *    Represent store as lambda.**
   *
   * Represent array stores as lambdas.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_FUN_STORE_LAMBDAS,

  /*! **Print DIMACS.**
   *
   * Print the CNF sent to the SAT solver in DIMACS format to stdout.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PRINT_DIMACS,

  /*! **Stochastic local search solver engine:
   *    Number of bit flips.**
   *
   * Configure the number of bit flips used as a limit for the SLS engine.
   *
   * Values:
   *  * An unsigned integer value, no limit if 0 (**default**: 0).
   */
  BITWUZLA_OPT_SLS_NFLIPS,

  /*! **Stochastic local search solver engine:
   *    Move strategy.**
   *
   * Configure the move selection strategy for the SLS engine.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_SLS_STRATEGY,

  /*! **Stochastic local search solver engine:
   *    Justification-based path selection.**
   *
   * Configure justification-based path selection for SLS engine.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_JUST,

  /*! **Stochastic local search solver engine:
   *    Group-wise moves.**
   *
   * Configure group-wise moves for SLS engine. When enabled, rather than
   * changing the assignment of one single candidate variable, all candidates
   * are set at the same time (using the same strategy).
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_MOVE_GW,

  /*! **Stochastic local search solver engine:
   *    Range-wise bit-flip moves.**
   *
   * Configure range-wise bit-flip moves for SLS engine. When enabled, try
   * range-wise bit-flips when selecting moves, where bits within all ranges
   * from 2 to the bit-width (starting from the LSB) are flipped at once.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_MOVE_RANGE,

  /*! **Stochastic local search solver engine:
   *    Segment-wise bit-flip moves.**
   *
   * Configure range-wise bit-flip moves for SLS engine. When enabled, try
   * segment-wise bit-flips when selecting moves, where bits within segments 
   * of multiples of 2 are flipped at once.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_MOVE_SEGMENT,

  /*! **Stochastic local search solver engine:
   *    Random walk.**
   *
   * Configure random walk moves, where one out of all possible neighbors is
   * randomly selected (with given probability
   * ::BITWUZLA_OPT_SLS_PROB_MOVE_RAND_WALK) for a randomly selected candidate
   * variable.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   *
   * @see BITWUZLA_OPT_SLS_MOVE_PROB_RAND_WALK
   */
  BITWUZLA_OPT_SLS_MOVE_RAND_WALK,

  /*! **Stochastic local search solver engine:
   *    Probability for random walks.**
   *
   * Configure the probability with which a random walk is chosen if random
   * walks are enabled.
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 100)
   *
   * @see BITWUZLA_OPT_SLS_MOVE_RAND_WALK
   */
  BITWUZLA_OPT_SLS_PROB_MOVE_RAND_WALK,

  /*! **Stochastic local search solver engine:
   *    Randomize all candidates.**
   *
   * Configure the randomization of all candidate variables (rather than just
   * a single randomly selected one) in case no best move has been found.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_MOVE_RAND_ALL,

  /*! **Stochastic local search solver engine:
   *    Randomize bit ranges.**
   *
   * Configure the randomization of bit ranges (rather than all bits) of
   * candidate variable(s) in case no best move has been found.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_MOVE_RAND_RANGE,

  /*! **Stochastic local search solver engine:
   *    Propagation moves.**
   *
   * Configure propagation moves, chosen with a ratio of number of propagation
   * moves ::BITWUZLA_OPT_SLS_MOVE_PROP_N_PROP to regular SLS moves
   * ::BITWUZLA_OPT_SLS_MOVE_PROP_N_SLS.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_MOVE_PROP,

  /*! **Stochastic local search solver engine:
   *    Number of propagation moves.**
   *
   * Configure the number of propagation moves to be performed when propagation
   * moves are enabled. Propagation moves are chosen with a ratio of
   * ::BITWUZLA_OPT_SLS_MOVE_PROP_N_PROP to ::BITWUZLA_OPT_SLS_MOVE_PROP_N_SLS.
   *
   * Values:
   *  * An unsigned integer value (**default**: 1)
   *
   * @see BITWUZLA_OPT_SLS_MOVE_PROP
   * @see BITWUZLA_OPT_SLS_MOVE_PROP_N_SLS
   */
  BITWUZLA_OPT_SLS_MOVE_PROP_N_PROP,

  /*! **Stochastic local search solver engine:
   *    Number of regular SLS moves.**
   *
   * Configure the number of regular SLS moves to be performed when propagation
   * moves are enabled. Propagation moves are chosen with a ratio of
   * ::BITWUZLA_OPT_SLS_MOVE_PROP_N_PROP to ::BITWUZLA_OPT_SLS_MOVE_PROP_N_SLS.
   *
   * Values:
   *  * An unsigned integer value (**default**: 1)
   *
   * @see BITWUZLA_OPT_SLS_MOVE_PROP
   * @see BITWUZLA_OPT_SLS_MOVE_PROP_N_PROP
   */
  BITWUZLA_OPT_SLS_MOVE_PROP_N_SLS,

  /*! **Stochastic local search solver engine:
   *    Force random walks.**
   *
   * Configure that random walks are forcibly chosen as recovery moves in case
   * of conflicts when a propagation move is performed (rather than performing
   * a regular SLS move).
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_MOVE_PROP_FORCE_RW,

  /*! **Stochastic local search solver engine:
   *    Incremental move test.**
   *
   * Configure that during best move selection, the previous best neighbor
   * for the current candidate is used for neighborhood exploration rather
   * than its current assignment.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_SLS_MOVE_INC_MOVE_TEST,

  /*! **Stochastic local search solver engine:
   *    Restarts.**
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_SLS_USE_RESTARTS,

  /*! **Stochastic local search solver engine:
   *    Bandit scheme.**
   *
   * Configure bandit scheme heuristic for selecting root constraints.
   * If disabled, root constraints are selected randomly.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_SLS_USE_BANDIT,

  /*! **Propagation-based local search solver engine:
   *    Number of propagations.**
   *
   * Configure the number of propagations used as a limit for the
   * propagation-based local search solver engine. No limit if 0.
   *
   * Values:
   *  * An unsigned integer value (**default**: 0).
   */
  BITWUZLA_OPT_PROP_NPROPS,

  /*! **Propagation-based local search solver engine:
   *    Number of updates.**
   *
   * Configure the number of model value updates used as a limit for the
   * propagation-based local search solver engine. No limit if 0.
   *
   * Values:
   *  * An unsigned integer value (**default**: 0).
   */
  BITWUZLA_OPT_PROP_NUPDATES,

  /*! **Propagation-based local search solver engine:
   *    Entailed propagations.**
   *
   * Maintain a work queue with entailed propagations.  
   * If enabled, propagations from this queue are propagated before randomly
   * choosing a yet unsatisfied path from the root.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_PROP_ENTAILED,

  /*! **Propagation-based local search solver engine:
   *    Constant bits.**
   *
   * Configure constant bit propagation (requries bit-blasting to AIG).
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_PROP_CONST_BITS,

  /*! **Propagation-based local search solver engine:
   *    Domain propagators.**
   *
   * Configure the use of domain propagators for determining constant bits
   * (instead of bit-blastin to AIG).
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_CONST_DOMAINS,

  /*! **Propagation-based local search solver engine:
   *    Restarts.**
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_USE_RESTARTS,

  /*! **Propagation-based local search solver engine:
   *    Bandit scheme.**
   *
   * Configure bandit scheme heuristic for selecting root constraints.  
   * If enabled, root constraint selection via bandit scheme is based on a
   * scoring scheme similar to the one used in the SLS engine.  
   * If disabled, root constraints are selected randomly.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_USE_BANDIT,

  /*! **Propagation-based local search solver engine:
   *    Path selection.**
   *
   * Configure mode for path selection.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_PROP_PATH_SEL,

  /*! **Propagation-based local search solver engine:
   *    Probability for inverse values.**
   *
   * Configure the probability with which to choose an inverse value over a
   * consistent value when aninverse value exists. 
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 990).
   */
  BITWUZLA_OPT_PROP_PROB_USE_INV_VALUE,

  /*! **Propagation-based local search solver engine:
   *    Probability for flipping ite condition.**
   *
   * Configure the probability with which to select the path to the condition
   * (in case of an ite operation) rather than the enabled branch during down
   * propagation).
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 100).
   */
  BITWUZLA_OPT_PROP_PROB_FLIP_COND,

  /*! **Propagation-based local search solver engine:
   *    Probability for flipping ite condition with constant branches.**
   *
   * Configure the probability with which to select the path to the condition
   * (in case of an ite operation) rather than the enabled branch during down
   * propagation) if either the 'then' or 'else' branch is constant.
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 100).
   */
  BITWUZLA_OPT_PROP_PROB_FLIP_COND_CONST,

  /*! **Propagation-based local search solver engine:
   *    Delta for flipping ite conditions with constant branches.**
   *
   * Configure the delta by which ::BITWUZLA_OPT_PROP_PROB_FLIP_COND_CONST is
   * decreased or increased after a limit
   * ::BITWUZLA_OPT_PROP_FLIP_COND_CONST_NPATHSEL is reached.
   *
   * Values:
   *  * A signed integer value (**default**: 100).
   */
  BITWUZLA_OPT_PROP_FLIP_COND_CONST_DELTA,

  /*! **Propagation-based local search solver engine:
   *    Limit for flipping ite conditions with constant branches.**
   *
   * Configure the limit for how often the path to the condition for ite
   * operations with constant branches may be selected before
   * ::BITWUZLA_OPT_PROP_PROB_FLIP_COND_CONST is decreased or increased by
   * ::BITWUZLA_OPT_PROP_FLIP_COND_CONST_DELTA.
   *
   * Values:
   *  * A signed integer value (**default**: 500).
   */
  BITWUZLA_OPT_PROP_FLIP_COND_CONST_NPATHSEL,

  /*! **Propagation-based local search solver engine:
   *    Probability for keeping the value of don't care bits for extracts.**
   *
   * Configure the probability with which to keep the current value of don't
   * care bits of an extract operation (rather than fully randomizing them)
   * when selecting an inverse or consistent value.
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 500).
   */
  BITWUZLA_OPT_PROP_PROB_SLICE_KEEP_DC,

  /*! **Propagation-based local search solver engine:
   *    Probability for flipping one of the don't care bits for extracts.**
   *
   * Configure the probability with which to flip one of the don't care bits of
   * the current assignment of the operand to a bit-vector extract (when the
   * asignment is kept) when selecting an inverse or consistent value.
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 0).
   *
   * @see ::BITWUZLA_OPT_PROP_PROB_SLICE_KEEP_DC
   */
  BITWUZLA_OPT_PROP_PROB_SLICE_FLIP,

  /*! **Propagation-based local search solver engine:
   *    Probability for using the current assignment with one bit flipped for
   *    equalities.**
   *
   * Configure the probability with which the current assignment of an operand
   * to a disequality is kept with just a single bit flipped (rather than fully
   * randomizing the assignment) when selecting an inverse or consistent value.
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 0).
   */
  BITWUZLA_OPT_PROP_PROB_EQ_FLIP,

  /*! **Propagation-based local search solver engine:
   *    Probability for flipping one of the don't care bits for ands.**
   *
   * Configure the probability with which to keep the current assignement of
   * the operand to a bit-vector and with max one bit flipped (rather than
   * fully randomizing the assignment) when selecting an inverse or consistent
   * value.
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 0).
   */
  BITWUZLA_OPT_PROP_PROB_AND_FLIP,

  /*! **Propagation-based local search solver engine:
   *    Probability for selecting random input.**
   *
   * Configure the probability with which to select a random input instead of
   * an essential input when selecting the path.
   *
   *
   * Values:
   *  * An unsigned integer value <= 1000 (= 100%) (**default**: 0).
   */
  BITWUZLA_OPT_PROP_PROB_RANDOM_INPUT,

  /*! **Propagation-based local search solver engine:
   *    No move on conflict.**
   *
   * When enabled, no move is performed when running into a conflict during
   * value computation.
   *
   * @note This is the default behavior for the SLS engine when propagation
   *       moves are enabled, where a conflict triggers a recovery by means
   *       of a regular SLS move.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_NO_MOVE_ON_CONFLICT,

  /*! **Propagation-based local search solver engine:
   *    Skip if no progress.**
   *
   * When enabled, moves that make no progress, that is, that produce a target
   * value that is the seame as the current assignment of a variable, are
   * skipped.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_SKIP_NO_PROGRESS,

  /*! **Propagation-based local search solver engine:
   *    Inverse value computation for inequalities over concats.**
   *
   * When enabled, use special inverse value computation for inequality over
   * concats.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_USE_INV_LT_CONCAT,

  /*! **Propagation-based local search solver engine:
   *    Infer bounds for inequalities for value computation.**
   *
   * When enabled, infer bounds for value computation for inequalities based on
   * satisfied top level inequalities.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_INFER_INEQ_BOUNDS,

  /*! **Propagation-based local search solver engine:
   *    Value computation for sign extension.**
   *
   * When enabled, detect sign extension operations (are rewritten on
   * construction) and use value computation for sign extension.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_SEXT,

  /*! **Propagation-based local search solver engine:
   *    Value computation for xor.**
   *
   * When enabled, detect xor operations (are rewritten on construction) and
   * use value computation for xor.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_XOR,

  /*! **Propagation-based local search solver engine:
   *    Value computation for xor.**
   *
   * When enabled, detect arithmetic right shift operations (are rewritten on
   * construction) and use value computation for ashr.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_PROP_ASHR,

  /*! **AIG-level propagation-based local search solver engine:
   *    Restarts.**
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_AIGPROP_USE_RESTARTS,

  /*! **AIG-level propagation-based local search solver engine:
   *    Bandit scheme.**
   *
   * Configure bandit scheme heuristic for selecting root constraints.  
   * If enabled, root constraint selection via bandit scheme is based on a
   * scoring scheme similar to the one used in the SLS engine.  
   * If disabled, root constraints are selected randomly.
   *
   * Values:
   *  * **1**: enable
   *  * **0**: disable [**default**]
   */
  BITWUZLA_OPT_AIGPROP_USE_BANDIT,

  /*! **AIG-level propagation-based local search solver engine:
   *    Number of propagations.**
   *
   * Configure the number of propagations used as a limit for the
   * propagation-based local search solver engine. No limit if 0.
   *
   * Values:
   *  * An unsigned integer value (**default**: 0).
   */
  BITWUZLA_OPT_AIGPROP_NPROPS,

  /*! **Quantifier solver engine:
   *    Synthesis mode.**
   *
   * Configure mode for synthesizing Skolem functions.
   *
   * Values: TODO
   */
  BITWUZLA_OPT_QUANT_SYNTH,

  /*! **Quantifier solver engine:
   *    Dual solver.**
   *
   * Configure the use of the dual (negated) version of the quantified formula.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_QUANT_DUAL_SOLVER,

  /*! **Quantifier solver engine:
   *    Limit for synthesis.**
   *
   * Configure the limit of enumerated expressions for the enumerative learning
   * synthesis algorithm implemented in the quantified solver engine.
   *
   * Values:
   *  * An unsigned integer value (**default**: 10000).
   */
  BITWUZLA_OPT_QUANT_SYNTH_LIMIT,

  /*! **Quantifier solver engine:
   *    Quantifier instantiation.**
   *
   * Configure the generalization of quantifier instantiations via enumerative
   * learning.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_QUANT_SYNTH_QI,

  /*! **Quantifier solver engine:
   *    Destructive Equality Resolution.**
   *
   * Configure the use of Destructive Equality Resolution simplification in
   * the quantifier solver engine.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_QUANT_DER,

  /*! **Quantifier solver engine:
   *    Constructive Equality Resolution.**
   *
   * Configure the use of Constructive Equality Resolution simplification in
   * the quantifier solver engine.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_QUANT_CER,

  /*! **Quantifier solver engine:
   *    Miniscoping.**
   *
   * Configure the use of miniscoping in the quantifier solver engine.
   *
   * Values:
   *  * **1**: enable [**default**]
   *  * **0**: disable
   */
  BITWUZLA_OPT_QUANT_MINISCOPE,
#ifndef DOXYGEN_SKIP
  /* internal options --------------------------------------------------- */
  BITWUZLA_OPT_SORT_EXP,
  BITWUZLA_OPT_SORT_AIG,
  BITWUZLA_OPT_SORT_AIGVEC,
  BITWUZLA_OPT_SIMPLIFY_CONSTRAINTS,
  BITWUZLA_OPT_CHECK_UNSAT_ASSUMPTIONS,
  BITWUZLA_OPT_CHECK_MODEL,
  BITWUZLA_OPT_CHECK_UNCONSTRAINED,
  BITWUZLA_OPT_LS_SHARE_SAT,
  BITWUZLA_OPT_PARSE_INTERACTIVE,
  BITWUZLA_OPT_SAT_ENGINE_LGL_FORK,
  BITWUZLA_OPT_SAT_ENGINE_CADICAL_FREEZE,
  BITWUZLA_OPT_SAT_ENGINE_N_THREADS,
  BITWUZLA_OPT_SLT_ELIM,
  BITWUZLA_OPT_SIMP_NORMAMLIZE_ADDERS,
  BITWUZLA_OPT_DECLSORT_BV_WIDTH,
  BITWUZLA_OPT_QUANT_SYNTH_ITE_COMPLETE,
  BITWUZLA_OPT_QUANT_FIXSYNTH,
  BITWUZLA_OPT_RW_ZERO_LOWER_SLICE,
  BITWUZLA_OPT_NONDESTR_SUBST,
  BITWUZLA_OPT_PROP_PROB_FALLBACK_RANDOM_VALUE,
  BITWUZLA_OPT_PRODUCE_UNSAT_CORES,
  BITWUZLA_OPT_SMT_COMP_MODE,
  /* this MUST be the last entry! */
  BITWUZLA_OPT_NUM_OPTS,
#endif
};
#ifndef DOXYGEN_SKIP
typedef enum BitwuzlaOption BitwuzlaOption;
#endif

/** The term kind. */
enum BitwuzlaKind
{
  /*! Boolean and.
   *
   *  SMT-LIB: \c and */
  BITWUZLA_KIND_AND,
  /*! Function application. */
  BITWUZLA_KIND_APPLY,
  /*! Array select.
   *
   *  SMT-LIB: \c select */
  BITWUZLA_KIND_ARRAY_SELECT,
  /*! Array store.
   *
   * SMT-LIB: \c store */
  BITWUZLA_KIND_ARRAY_STORE,
  /*! Bit-vector addition.
   *
   *  SMT-LIB: \c bvadd */
  BITWUZLA_KIND_BV_ADD,
  /*! Bit-vector and.
   *
   * SMT-LIB: \c bvand */
  BITWUZLA_KIND_BV_AND,
  /*! Bit-vector arithmetic right shift.
   *
   * SMT-LIB: \c bvashr */
  BITWUZLA_KIND_BV_ASHR,
  /*! Bit-vector comparison.
   *
   * SMT-LIB: \c bvcomp */
  BITWUZLA_KIND_BV_COMP,
  /*! Bit-vector concat.
   *
   * SMT-LIB: \c concat */
  BITWUZLA_KIND_BV_CONCAT,
  /*! Bit-vector decrement.
   *
   * Decrement by one. */
  BITWUZLA_KIND_BV_DEC,
  /*! Bit-vector increment.
   *
   * Increment by one. */
  BITWUZLA_KIND_BV_INC,
  /*! Bit-vector multiplication.
   *
   * SMT-LIB: \c bvmul */
  BITWUZLA_KIND_BV_MUL,
  /*! Bit-vector nand.
   *
   * SMT-LIB: \c bvnand */
  BITWUZLA_KIND_BV_NAND,
  /*! Bit-vector negation (two's complement).
   *
   * SMT-LIB: \c bvneg */
  BITWUZLA_KIND_BV_NEG,
  /*! Bit-vector nor.
   *
   * SMT-LIB: \c bvnor */
  BITWUZLA_KIND_BV_NOR,
  /*! Bit-vector not (one's complement).
   *
   * SMT-LIB: \c bvnot */
  BITWUZLA_KIND_BV_NOT,
  /*! Bit-vector or.
   *
   * SMT-LIB: \c bvor */
  BITWUZLA_KIND_BV_OR,
  /*! Bit-vector and reduction.
   *
   * Bit-wise \c and reduction, all bits are \c and ed together into a single bit.
   * This corresponds to bit-wise \c and reduction as known from Verilog. */
  BITWUZLA_KIND_BV_REDAND,
  /*! Bit-vector reduce or.
   *
   * Bit-wise \c or reduction, all bits are \c or ed together into a single bit.
   * This corresponds to bit-wise \c or reduction as known from Verilog. */
  BITWUZLA_KIND_BV_REDOR,
  /*! Bit-vector reduce xor.
   *
   * Bit-wise \c xor reduction, all bits are \c xor ed together into a single bit.
   * This corresponds to bit-wise \c xor reduction as known from Verilog. */
  BITWUZLA_KIND_BV_REDXOR,
  /*! Bit-vector rotate left (not indexed).
   *
   * This is a non-indexed variant of SMT-LIB \c rotate_left. */
  BITWUZLA_KIND_BV_ROL,
  /*! Bit-vector rotate right.
   *
   * This is a non-indexed variant of SMT-LIB \c rotate_right. */
  BITWUZLA_KIND_BV_ROR,
  /*! Bit-vector signed addition overflow test.
   *
   * Single bit to indicate if signed addition produces an overflow. */
  BITWUZLA_KIND_BV_SADD_OVERFLOW,
  /*! Bit-vector signed division overflow test.
   *
   * Single bit to indicate if signed division produces an overflow. */
  BITWUZLA_KIND_BV_SDIV_OVERFLOW,
  /*! Bit-vector signed division.
   *
   * SMT-LIB: \c bvsdiv */
  BITWUZLA_KIND_BV_SDIV,
  /*! Bit-vector signed greater than or equal.
   *
   * SMT-LIB: \c bvsle */
  BITWUZLA_KIND_BV_SGE,
  /*! Bit-vector signed greater than.
   *
   * SMT-LIB: \c bvslt */
  BITWUZLA_KIND_BV_SGT,
  /*! Bit-vector logical left shift.
   *
   * SMT-LIB: \c bvshl */
  BITWUZLA_KIND_BV_SHL,
  /*! Bit-vector logical right shift.
   *
   * SMT-LIB: \c bvshr */
  BITWUZLA_KIND_BV_SHR,
  /*! Bit-vector signed less than or equal.
   *
   * SMT-LIB: \c bvsle */
  BITWUZLA_KIND_BV_SLE,
  /*! Bit-vector signed less than.
   *
   * SMT-LIB: \c bvslt */
  BITWUZLA_KIND_BV_SLT,
  /*! Bit-vector signed modulo.
   *
   * SMT-LIB: \c bvsmod */
  BITWUZLA_KIND_BV_SMOD,
  /*! Bit-vector signed multiplication overflow test.
   *
   * SMT-LIB: \c bvsmod */
  BITWUZLA_KIND_BV_SMUL_OVERFLOW,
  /*! Bit-vector signed remainder.
   *
   * SMT-LIB: \c bvsrem */
  BITWUZLA_KIND_BV_SREM,
  /*! Bit-vector signed subtraction overflow test.
   *
   * Single bit to indicate if signed subtraction produces an overflow. */
  BITWUZLA_KIND_BV_SSUB_OVERFLOW,
  /*! Bit-vector subtraction.
   *
   * SMT-LIB: \c bvsub */
  BITWUZLA_KIND_BV_SUB,
  /*! Bit-vector unsigned addition overflow test.
   *
   * Single bit to indicate if unsigned addition produces an overflow. */
  BITWUZLA_KIND_BV_UADD_OVERFLOW,
  /*! Bit-vector unsigned division.
   *
   * SMT-LIB: \c bvudiv */
  BITWUZLA_KIND_BV_UDIV,
  /*! Bit-vector unsigned greater than or equal.
   *
   * SMT-LIB: \c bvuge */
  BITWUZLA_KIND_BV_UGE,
  /*! Bit-vector unsigned greater than.
   *
   * SMT-LIB: \c bvugt */
  BITWUZLA_KIND_BV_UGT,
  /*! Bit-vector unsigned less than or equal.
   *
   * SMT-LIB: \c bvule */
  BITWUZLA_KIND_BV_ULE,
  /*! Bit-vector unsigned less than.
   *
   * SMT-LIB: \c bvult */
  BITWUZLA_KIND_BV_ULT,
  /*! Bit-vector unsigned multiplication overflow test.
   *
   * Single bit to indicate if unsigned multiplication produces an overflow. */
  BITWUZLA_KIND_BV_UMUL_OVERFLOW,
  /*! Bit-vector unsigned remainder.
   *
   * SMT-LIB: \c bvurem */
  BITWUZLA_KIND_BV_UREM,
  /*! Bit-vector unsigned subtraction overflow test.
   *
   * Single bit to indicate if unsigned subtraction produces an overflow. */
  BITWUZLA_KIND_BV_USUB_OVERFLOW,
  /*! Bit-vector xnor.
   *
   * SMT-LIB: \c bvxnor */
  BITWUZLA_KIND_BV_XNOR,
  /*! Bit-vector xor.
   *
   * SMT-LIB: \c bvxor */
  BITWUZLA_KIND_BV_XOR,
  /*! Disequality.
   *
   * SMT-LIB: \c distinct */
  BITWUZLA_KIND_DISTINCT,
  /*! Equality.
   *
   * SMT-LIB: \c = */
  BITWUZLA_KIND_EQUAL,
  /*! Existential quantification.
   *
   * SMT-LIB: \c exists */
  BITWUZLA_KIND_EXISTS,
  /*! Universal quantification.
   *
   * SMT-LIB: \c forall */
  BITWUZLA_KIND_FORALL,
  /*! Floating-point absolute value.
   *
   * SMT-LIB: \c fp.abs */
  BITWUZLA_KIND_FP_ABS,
  /*! Floating-point addition.
   *
   * SMT-LIB: \c fp.add */
  BITWUZLA_KIND_FP_ADD,
  /*! Floating-point division.
   *
   * SMT-LIB: \c fp.div */
  BITWUZLA_KIND_FP_DIV,
  /*! Floating-point equality.
   *
   * SMT-LIB: \c fp.eq */
  BITWUZLA_KIND_FP_EQ,
  /*! Floating-point fused multiplcation and addition.
   *
   * SMT-LIB: \c fp.fma */
  BITWUZLA_KIND_FP_FMA,
  /*! Floating-point IEEE 754 value.
   *
   * SMT-LIB: \c fp */
  BITWUZLA_KIND_FP_FP,
  /*! Floating-point greater than or equal.
   *
   * SMT-LIB: \c fp.geq */
  BITWUZLA_KIND_FP_GEQ,
  /*! Floating-point greater than.
   *
   * SMT-LIB: \c fp.gt */
  BITWUZLA_KIND_FP_GT,
  /*! Floating-point is infinity tester.
   *
   * SMT-LIB: \c fp.isInfinite */
  BITWUZLA_KIND_FP_IS_INF,
  /*! Floating-point is Nan tester.
   *
   * SMT-LIB: \c fp.isNaN */
  BITWUZLA_KIND_FP_IS_NAN,
  /*! Floating-point is negative tester.
   *
   * SMT-LIB: \c fp.isNegative */
  BITWUZLA_KIND_FP_IS_NEG,
  /*! Floating-point is normal tester.
   *
   * SMT-LIB: \c fp.isNormal */
  BITWUZLA_KIND_FP_IS_NORMAL,
  /*! Floating-point is positive tester.
   *
   * SMT-LIB: \c fp.isPositive */
  BITWUZLA_KIND_FP_IS_POS,
  /*! Floating-point is subnormal tester.
   *
   * SMT-LIB: \c fp.isSubnormal */
  BITWUZLA_KIND_FP_IS_SUBNORMAL,
  /*! Floating-point is zero tester.
   *
   * SMT-LIB: \c fp.isZero */
  BITWUZLA_KIND_FP_IS_ZERO,
  /*! Floating-point less than or equal.
   *
   * SMT-LIB: \c fp.leq */
  BITWUZLA_KIND_FP_LEQ,
  /*! Floating-point less than.
   *
   * SMT-LIB: \c fp.lt */
  BITWUZLA_KIND_FP_LT,
  /*! Floating-point max.
   *
   * SMT-LIB: \c fp.max */
  BITWUZLA_KIND_FP_MAX,
  /*! Floating-point min.
   *
   * SMT-LIB: \c fp.min */
  BITWUZLA_KIND_FP_MIN,
  /*! Floating-point multiplcation.
   *
   * SMT-LIB: \c fp.mul */
  BITWUZLA_KIND_FP_MUL,
  /*! Floating-point negation.
   *
   * SMT-LIB: \c fp.neg */
  BITWUZLA_KIND_FP_NEG,
  /*! Floating-point remainder.
   *
   * SMT-LIB: \c fp.rem */
  BITWUZLA_KIND_FP_REM,
  /*! Floating-point round to integral.
   *
   * SMT-LIB: \c fp.roundToIntegral */
  BITWUZLA_KIND_FP_RTI,
  /*! Floating-point round to square root.
   *
   * SMT-LIB: \c fp.sqrt */
  BITWUZLA_KIND_FP_SQRT,
  /*! Floating-point round to subtraction.
   *
   * SMT-LIB: \c fp.sqrt */
  BITWUZLA_KIND_FP_SUB,
  /*! Boolean if and only if.
   *
   * SMT-LIB: \c = */
  BITWUZLA_KIND_IFF,
  /*! Boolean implies.
   *
   * SMT-LIB: \c => */
  BITWUZLA_KIND_IMPLIES,
  /*! If-then-else.
   *
   * SMT-LIB: \c ite */
  BITWUZLA_KIND_ITE,
  /*! Lambda. */
  BITWUZLA_KIND_LAMBDA,
  /*! Boolean not.
   *
   * SMT-LIB: \c not */
  BITWUZLA_KIND_NOT,
  /*! Boolean or.
   *
   * SMT-LIB: \c or */
  BITWUZLA_KIND_OR,
  /*! Boolean xor.
   *
   * SMT-LIB: \c xor */
  BITWUZLA_KIND_XOR,

  // indexed
  /*! Bit-vector extract.
   *
   * SMT-LIB: \c extract (indexed) */
  BITWUZLA_KIND_BV_EXTRACT,
  /*! Bit-vector repeat.
   *
   * SMT-LIB: \c repeat (indexed) */
  BITWUZLA_KIND_BV_REPEAT,
  /*! Bit-vector rotate left by integer.
   *
   * SMT-LIB: \c rotate_left (indexed) */
  BITWUZLA_KIND_BV_ROLI,
  /*! Bit-vector rotate right by integer.
   *
   * SMT-LIB: \c rotate_right (indexed) */
  BITWUZLA_KIND_BV_RORI,
  /*! Bit-vector sign extend.
   *
   * SMT-LIB: \c sign_extend (indexed) */
  BITWUZLA_KIND_BV_SIGN_EXTEND,
  /*! Bit-vector zero extend.
   *
   * SMT-LIB: \c zero_extend (indexed) */
  BITWUZLA_KIND_BV_ZERO_EXTEND,
  /*! Floating-point to_fp from IEEE 754 bit-vector.
   *
   * SMT-LIB: \c to_fp (indexed) */
  BITWUZLA_KIND_FP_TO_FP_FROM_BV,
  /*! Floating-point to_fp from floating-point.
   *
   * SMT-LIB: \c to_fp (indexed) */
  BITWUZLA_KIND_FP_TO_FP_FROM_FP,
  /*! Floating-point to_fp from signed bit-vector value.
   *
   * SMT-LIB: \c to_fp (indexed) */
  BITWUZLA_KIND_FP_TO_FP_FROM_SBV,
  /*! Floating-point to_fp from unsigned bit-vector value.
   *
   * SMT-LIB: \c to_fp_unsigned (indexed) */
  BITWUZLA_KIND_FP_TO_FP_FROM_UBV,
  /*! Floating-point to_sbv.
   *
   * SMT-LIB: \c fp.to_sbv (indexed) */
  BITWUZLA_KIND_FP_TO_SBV,
  /*! Floating-point to_ubv.
   *
   * SMT-LIB: \c fp.to_ubv (indexed) */
  BITWUZLA_KIND_FP_TO_UBV,
#ifndef DOXYGEN_SKIP
  BITWUZLA_NUM_KINDS,
#endif
};
#ifndef DOXYGEN_SKIP
typedef enum BitwuzlaKind BitwuzlaKind;
#endif

/** A satisfiability result. */
enum BitwuzlaResult
{
  BITWUZLA_SAT     = 10, ///< sat
  BITWUZLA_UNSAT   = 20, ///< unsat
  BITWUZLA_UNKNOWN = 0,  ///< unknown
};
#ifndef DOXYGEN_SKIP
typedef enum BitwuzlaResult BitwuzlaResult;
#endif

/** A roundingmode value. */
enum BitwuzlaRoundingMode
{
  /*! SMT-LIB: \c RNE \c roundNearestTiesToEven */
  BITWUZLA_RM_RNE = 0,
  /*! SMT-LIB: \c RNA \c roundNearestTiesToAway */
  BITWUZLA_RM_RNA = 1,
  /*! SMT-LIB: \c RTN \c roundTowardNegative */
  BITWUZLA_RM_RTN = 2,
  /*! SMT-LIB: \c RTP \c roundTowardPositive */
  BITWUZLA_RM_RTP = 3,
  /*! SMT-LIB: \c RTZ \c roundTowardZero */
  BITWUZLA_RM_RTZ = 4,
#ifndef DOXYGEN_SKIP
  BITWUZLA_RM_MAX = 5,
#endif
};
#ifndef DOXYGEN_SKIP
typedef enum BitwuzlaRoundingMode BitwuzlaRoundingMode;
#endif

/** The Bitwuzla solver. */
typedef struct Bitwuzla Bitwuzla;
/** A Bitwuzla term. */
typedef struct BitwuzlaTerm BitwuzlaTerm;
/** A Bitwuzla sort. */
typedef struct BitwuzlaSort BitwuzlaSort;

/* -------------------------------------------------------------------------- */
/* Bitwuzla                                                                   */
/* -------------------------------------------------------------------------- */

/**
 * Create a new Bitwuzla instance.
 *
 * The returned instance must be deleted via bitwuzla_delete().
 *
 * @return A pointer to the created Bitwuzla instance.
 *
 * @see bitwuzla_delete
 */
Bitwuzla *bitwuzla_new(void);

/**
 * Delete a Bitwuzla instance.
 *
 * The given instance must have been created via bitwuzla_new().
 *
 * @param bitwuzla The Bitwuzla instance to delete.
 *
 * @see bitwuzla_new
 */
void bitwuzla_delete(Bitwuzla *bitwuzla);

/**
 * Reset a Bitwuzla instance.
 *
 * This deletes the given instance and creates a new instance in place.
 * The given instance must have been created via bitwuzla_new().
 *
 * @note All sorts and terms associated with the given instance are released
 *       and thus invalidated.
 *
 * @param bitwuzla The Bitwuzla instance to reset.
 *
 * @see bitwuzla_new
 */
void bitwuzla_reset(Bitwuzla *bitwuzla);

/**
 * Print copyright information.
 *
 * @param bitwuzla The Bitwuzla instance.
 */
const char *bitwuzla_copyright(Bitwuzla *bitwuzla);

/**
 * Print version information.
 *
 * @param bitwuzla The Bitwuzla instance.
 */
const char *bitwuzla_version(Bitwuzla *bitwuzla);

/**
 * If termination callback function has been configured via
 * bitwuzla_set_termination_callback(), call this termination function.
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @return True if \p bitwuzla has been terminated.
 */
bool bitwuzla_terminate(Bitwuzla *bitwuzla);

/**
 * Configure a termination callback function.
 *
 * The \p state of the callback can be retrieved via
 * bitwuzla_get_termination_callback_state().
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param fun The callback function, returns a value > 0 if \p bitwuzla has
 *            been terminated.
 * @param state The argument to the callback function.
 *
 * @see bitwuzla_terminate
 * @see bitwuzla_get_termination_callback_state
 */
void bitwuzla_set_termination_callback(Bitwuzla *bitwuzla,
                                       int32_t (*fun)(void *),
                                       void *state);

/**
 * Get the state of the termination callback function.
 *
 * The returned object representing the state of the callback corresponds to
 * the \p state configured as argument to the callback function via
 * bitwuzla_get_termination_callback_state().
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @return The object passed as argument \p state to the callback function.
 *
 * @see bitwuzla_terminate
 * @see bitwuzla_set_termination_callback
 */
void *bitwuzla_get_termination_callback_state(Bitwuzla *bitwuzla);

/**
 * Configure an abort callback function, which is called instead of exit
 * on abort conditions.
 *
 * @note This function is not thread safe (the function pointer is maintained
 *       as a global variable). It you use threading, make sure to set the
 *       abort callback prior to creating threads.
 *
 * @param fun The callback function, the argument \p msg explains the reason
 *            for the abort.
 */
void bitwuzla_set_abort_callback(void (*fun)(const char *msg));

/**
 * Set option.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param option The option.
 * @param val The option value.
 *
 * @see BitwuzlaOption
 */
void bitwuzla_set_option(Bitwuzla *bitwuzla,
                         BitwuzlaOption option,
                         uint32_t val);

/**
 * Set option value for string options.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param option The option.
 * @param val The option string value.
 *
 * @see BitwuzlaOption
 */
void bitwuzla_set_option_str(Bitwuzla *bitwuzla,
                             BitwuzlaOption option,
                             const char *val);

/**
 * Get the current value of an option.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param option The option.
 *
 * @return The option value.
 *
 * @see BitwuzlaOption
 */
uint32_t bitwuzla_get_option(Bitwuzla *bitwuzla, BitwuzlaOption option);

/**
 * Create an array sort.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param index The index sort of the array sort.
 * @param element The element sort of the array sort.
 *
 * @return An array sort which maps sort \p index to sort \p element.
 *
 * @see bitwuzla_sort_is_array
 * @see bitwuzla_sort_array_get_index
 * @see bitwuzla_sort_array_get_element
 * @see bitwuzla_term_is_array
 * @see bitwuzla_term_array_get_index_sort
 * @see bitwuzla_term_array_get_element_sort
 */
BitwuzlaSort *bitwuzla_mk_array_sort(Bitwuzla *bitwuzla,
                                     const BitwuzlaSort *index,
                                     const BitwuzlaSort *element);

/**
 * Create a Boolean sort.
 *
 * @note A Boolean sort is a bit-vector sort of size 1.
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @return A Boolean sort.
 */
BitwuzlaSort *bitwuzla_mk_bool_sort(Bitwuzla *bitwuzla);

/**
 * Create a bit-vector sort of given size.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param size The size of the bit-vector sort.
 *
 * @return A bit-vector sort of given size.
 *
 * @see bitwuzla_sort_is_bv
 * @see bitwuzla_sort_bv_get_size
 * @see bitwuzla_term_is_bv
 * @see bitwuzla_term_bv_get_size
 */
BitwuzlaSort *bitwuzla_mk_bv_sort(Bitwuzla *bitwuzla, uint32_t size);

/**
 * Create a floating-point sort of given exponent and significand size.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param exp_size The size of the exponent.
 * @param sig_size The size of the significand (including sign bit).
 *
 * @return A floating-point sort of given format.
 *
 * @see bitwuzla_sort_is_fp
 * @see bitwuzla_sort_fp_get_exp_size
 * @see bitwuzla_sort_fp_get_sig_size
 * @see bitwuzla_term_is_fp
 * @see bitwuzla_term_fp_get_exp_size
 * @see bitwuzla_term_fp_get_sig_size
 */
BitwuzlaSort *bitwuzla_mk_fp_sort(Bitwuzla *bitwuzla,
                                  uint32_t exp_size,
                                  uint32_t sig_size);

/**
 * Create a function sort.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param arity The number of arguments to the function.
 * @param domain The domain sorts (the sorts of the arguments). The number of
 *               sorts in this vector must match \p arity.
 * @param codomain The codomain sort (the sort of the return value).
 *
 * @return A function sort of given domain and codomain sorts.
 *
 * @see bitwuzla_sort_is_fun
 * @see bitwuzla_sort_fun_get_arity
 * @see bitwuzla_sort_fun_get_domain
 * @see bitwuzla_sort_fun_get_domain_sorts
 * @see bitwuzla_sort_fun_get_codomain
 * @see bitwuzla_term_is_fun
 * @see bitwuzla_term_fun_get_arity
 * @see bitwuzla_term_fun_get_domain_sort
 * @see bitwuzla_term_fun_get_domain_sorts
 * @see bitwuzla_term_fun_get_codomain_sort
 */
BitwuzlaSort *bitwuzla_mk_fun_sort(Bitwuzla *bitwuzla,
                                   uint32_t arity,
                                   BitwuzlaSort *domain[],
                                   const BitwuzlaSort *codomain);

/**
 * Create a roundingmode sort.
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @return A roundingmode sort.
 *
 * @see bitwuzla_sort_is_rm
 * @see bitwuzla_term_is_rm
 */
BitwuzlaSort *bitwuzla_mk_rm_sort(Bitwuzla *bitwuzla);

/**
 * Create a true value.
 *
 * @note This creates a bit-vector value 1 of size 1.
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @return A term representing the bit-vector value 1 of size 1.
 */
BitwuzlaTerm *bitwuzla_mk_true(Bitwuzla *bitwuzla);

/**
 * Create a false value.
 *
 * @note This creates a bit-vector value 0 of size 1.
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @return A term representing the bit-vector value 0 of size 1.
 */
BitwuzlaTerm *bitwuzla_mk_false(Bitwuzla *bitwuzla);

/**
 * Create a bit-vector value zero.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the bit-vector value 0 of given sort.
 *
 * @see bitwuzla_mk_bv_sort
 */
BitwuzlaTerm *bitwuzla_mk_bv_zero(Bitwuzla *bitwuzla, const BitwuzlaSort *sort);

/**
 * Create a bit-vector value one.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the bit-vector value 1 of given sort.
 *
 * @see bitwuzla_mk_bv_sort
 */
BitwuzlaTerm *bitwuzla_mk_bv_one(Bitwuzla *bitwuzla, const BitwuzlaSort *sort);

/**
 * Create a bit-vector value where all bits are set to 1.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the bit-vector value of given sort
 *         where all bits are set to 1.
 *
 * @see bitwuzla_mk_bv_sort
 */
BitwuzlaTerm *bitwuzla_mk_bv_ones(Bitwuzla *bitwuzla, const BitwuzlaSort *sort);

/**
 * Create a bit-vector minimum signed value.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the bit-vector value of given sort where the MSB
 *         is set to 1 and all remaining bits are set to 0.
 *
 * @see bitwuzla_mk_bv_sort
 */
BitwuzlaTerm *bitwuzla_mk_bv_min_signed(Bitwuzla *bitwuzla,
                                        const BitwuzlaSort *sort);
/**
 * Create a bit-vector maximum signed value.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the bit-vector value of given sort where the MSB
 *         is set to 0 and all remaining bits are set to 1.
 *
 * @see bitwuzla_mk_bv_sort
 */
BitwuzlaTerm *bitwuzla_mk_bv_max_signed(Bitwuzla *bitwuzla,
                                        const BitwuzlaSort *sort);

/**
 * Create a floating-point positive zero value (+zero).
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the floating-point positive zero value of given
 *         floating-point sort.
 *
 * @see bitwuzla_mk_fp_sort
 */
BitwuzlaTerm *bitwuzla_mk_fp_pos_zero(Bitwuzla *bitwuzla,
                                      const BitwuzlaSort *sort);

/**
 * Create a floating-point negative zero value (-zero).
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the floating-point negative zero value of given
 *         floating-point sort.
 *
 * @see bitwuzla_mk_fp_sort
 */
BitwuzlaTerm *bitwuzla_mk_fp_neg_zero(Bitwuzla *bitwuzla,
                                      const BitwuzlaSort *sort);

/**
 * Create a floating-point positive infinity value (+oo).
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the floating-point positive infinity value of
 *         given floating-point sort.
 *
 * @see bitwuzla_mk_fp_sort
 */
BitwuzlaTerm *bitwuzla_mk_fp_pos_inf(Bitwuzla *bitwuzla,
                                     const BitwuzlaSort *sort);

/**
 * Create a floating-point negative infinity value (-oo).
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the floating-point negative infinity value of
 *         given floating-point sort.
 *
 * @see bitwuzla_mk_fp_sort
 */
BitwuzlaTerm *bitwuzla_mk_fp_neg_inf(Bitwuzla *bitwuzla,
                                     const BitwuzlaSort *sort);

/**
 * Create a floating-point NaN value.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 *
 * @return A term representing the floating-point NaN value of given
 *         floating-point sort.
 *
 * @see bitwuzla_mk_fp_sort
 */
BitwuzlaTerm *bitwuzla_mk_fp_nan(Bitwuzla *bitwuzla, const BitwuzlaSort *sort);

/**
 * Create a bit-vector value from its string representation.
 *
 * Parameter \p base determines the base of the string representation.
 *
 * @note Given value must fit into a bit-vector of given size (sort).
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 * @param value A string representing the value.
 * @param base The base in which the string is given.
 *
 * @return A term representing the bit-vector value of given sort.
 *
 * @see bitwuzla_mk_bv_sort
 * @see BitwuzlaBase
 */
BitwuzlaTerm *bitwuzla_mk_bv_value(Bitwuzla *bitwuzla,
                                   const BitwuzlaSort *sort,
                                   const char *value,
                                   BitwuzlaBVBase base);

/**
 * Create a bit-vector value from its unsigned integer representation.
 *
 * @note If given value does not fit into a bit-vector of given size (sort),
 *       the value is truncated to fit.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 * @param value The unsigned integer representation of the bit-vector value.
 *
 * @return A term representing the bit-vector value of given sort.
 *
 * @see bitwuzla_mk_bv_sort
 */
BitwuzlaTerm *bitwuzla_mk_bv_value_uint64(Bitwuzla *bitwuzla,
                                          const BitwuzlaSort *sort,
                                          uint64_t value);

/**
 * Create a floating-point value from its IEEE 754 standard representation
 * given as three bitvectors representing the sign bit, the exponent and the
 * significand.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param bv_sign The sign bit.
 * @param bv_exponent The exponent bit-vector.
 * @param bv_significand The significand bit-vector.
 *
 * @return A term representing the floating-point value.
 */
BitwuzlaTerm *bitwuzla_mk_fp_value(Bitwuzla *bitwuzla,
                                   const BitwuzlaTerm *bv_sign,
                                   const BitwuzlaTerm *bv_exponent,
                                   const BitwuzlaTerm *bv_significand);

/**
 * Create a floating-point value from its real representation, given as a
 * decimal string, with respect to given roundingmode.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 * @param rm The roundingmode.
 * @param real The decimal string representing a real value.
 *
 * @return A term representing the floating-point value of given sort.
 *
 * @see bitwuzla_mk_fp_sort
 */
BitwuzlaTerm *bitwuzla_mk_fp_value_from_real(Bitwuzla *bitwuzla,
                                             const BitwuzlaSort *sort,
                                             const BitwuzlaTerm *rm,
                                             const char *real);

/**
 * Create a floating-point value from its rational representation, given as a
 * two decimal strings representing the numerator and denominator, with respect
 * to given roundingmode.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the value.
 * @param rm The roundingmode.
 * @param num The decimal string representing the numerator.
 * @param den The decimal string representing the denominator.
 *
 * @return A term representing the floating-point value of given sort.
 *
 * @see bitwuzla_mk_fp_sort
 */
BitwuzlaTerm *bitwuzla_mk_fp_value_from_rational(Bitwuzla *bitwuzla,
                                                 const BitwuzlaSort *sort,
                                                 const BitwuzlaTerm *rm,
                                                 const char *num,
                                                 const char *den);

/**
 * Create a roundingmode value.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param rm The rounding mode value.
 *
 * @return A term representing the roundingmode value.
 *
 * @see BitwuzlaRoundingMode
 */
BitwuzlaTerm *bitwuzla_mk_rm_value(Bitwuzla *bitwuzla, BitwuzlaRoundingMode rm);

/**
 * Create a term of given kind with one argument term.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param arg The argument to the operator.
 *
 * @return A term representing an operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term1(Bitwuzla *bitwuzla,
                                BitwuzlaKind kind,
                                const BitwuzlaTerm *arg);

/**
 * Create a term of given kind with two argument terms.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param arg0 The first argument to the operator.
 * @param arg1 The second argument to the operator.
 *
 * @return A term representing an operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term2(Bitwuzla *bitwuzla,
                                BitwuzlaKind kind,
                                const BitwuzlaTerm *arg0,
                                const BitwuzlaTerm *arg1);

/**
 * Create a term of given kind with three argument terms.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param arg0 The first argument to the operator.
 * @param arg1 The second argument to the operator.
 * @param arg2 The third argument to the operator.
 *
 * @return A term representing an operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term3(Bitwuzla *bitwuzla,
                                BitwuzlaKind kind,
                                const BitwuzlaTerm *arg0,
                                const BitwuzlaTerm *arg1,
                                const BitwuzlaTerm *arg2);

/**
 * Create a term of given kind with the given argument terms.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param argc The number of argument terms.
 * @param args The argument terms.
 *
 * @return A term representing an operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term(Bitwuzla *bitwuzla,
                               BitwuzlaKind kind,
                               uint32_t argc,
                               BitwuzlaTerm *args[]);

/**
 * Create an indexed term of given kind with one argument term and one index.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param arg The argument term.
 * @param idx The index.
 *
 * @return A term representing an indexed operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term1_indexed1(Bitwuzla *bitwuzla,
                                         BitwuzlaKind kind,
                                         const BitwuzlaTerm *arg,
                                         uint32_t idx);

/**
 * Create an indexed term of given kind with one argument term and two indices.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param arg The argument term.
 * @param idx0 The first index.
 * @param idx1 The second index.
 *
 * @return A term representing an indexed operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term1_indexed2(Bitwuzla *bitwuzla,
                                         BitwuzlaKind kind,
                                         const BitwuzlaTerm *arg,
                                         uint32_t idx0,
                                         uint32_t idx1);

/**
 * Create an indexed term of given kind with two argument terms and one index.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param arg0 The first argument term.
 * @param arg1 The second argument term.
 * @param idx The index.
 *
 * @return A term representing an indexed operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term2_indexed1(Bitwuzla *bitwuzla,
                                         BitwuzlaKind kind,
                                         const BitwuzlaTerm *arg0,
                                         const BitwuzlaTerm *arg1,
                                         uint32_t idx);

/**
 * Create an indexed term of given kind with two argument terms and two indices.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param arg0 The first argument term.
 * @param arg1 The second argument term.
 * @param idx0 The first index.
 * @param idx1 The second index.
 *
 * @return A term representing an indexed operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term2_indexed2(Bitwuzla *bitwuzla,
                                         BitwuzlaKind kind,
                                         const BitwuzlaTerm *arg0,
                                         const BitwuzlaTerm *arg1,
                                         uint32_t idx0,
                                         uint32_t idx1);

/**
 * Create an indexed term of given kind with the given argument terms and
 * indices.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param kind The operator kind.
 * @param argc The number of argument terms.
 * @param args The argument terms.
 * @param idxc The number of indices.
 * @param idxs The indices.
 *
 * @return A term representing an indexed operation of given kind.
 *
 * @see BitwuzlaKind
 */
BitwuzlaTerm *bitwuzla_mk_term_indexed(Bitwuzla *bitwuzla,
                                       BitwuzlaKind kind,
                                       uint32_t argc,
                                       BitwuzlaTerm *args[],
                                       uint32_t idxc,
                                       uint32_t idxs[]);

/**
 * Create a (first-order) constant of given sort with given symbol.
 *
 * @note This creates a 0-arity function symbol.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the constant.
 * @param symbol The symbol of the constant.
 *
 * @return A term representing the constant.
 *
 * @see bitwuzla_mk_array_sort
 * @see bitwuzla_mk_bool_sort
 * @see bitwuzla_mk_bv_sort
 * @see bitwuzla_mk_fp_sort
 * @see bitwuzla_mk_fun_sort
 * @see bitwuzla_mk_rm_sort
 */
BitwuzlaTerm *bitwuzla_mk_const(Bitwuzla *bitwuzla,
                                const BitwuzlaSort *sort,
                                const char *symbol);

/**
 * Create a one-dimensional constant array of given sort, initialized with
 * given value.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the array.
 * @param value The value to initialize the elements of the array with.
 *
 * @return A term representing a constant array of given sort.
 *
 * @see bitwuzla_mk_array_sort
 */
BitwuzlaTerm *bitwuzla_mk_const_array(Bitwuzla *bitwuzla,
                                      const BitwuzlaSort *sort,
                                      const BitwuzlaTerm *value);

/**
 * Create a variable of given sort with given symbol.
 *
 * @note This creates a variable to be bound by quantifiers or lambdas.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param sort The sort of the variable.
 * @param symbol The symbol of the variable.
 *
 * @return A term representing the variable.
 *
 * @see bitwuzla_mk_bool_sort
 * @see bitwuzla_mk_bv_sort
 * @see bitwuzla_mk_fp_sort
 * @see bitwuzla_mk_fun_sort
 * @see bitwuzla_mk_rm_sort
 */
BitwuzlaTerm *bitwuzla_mk_var(Bitwuzla *bitwuzla,
                              const BitwuzlaSort *sort,
                              const char *symbol);

/**
 * Push context levels.
 *
 * Requires that incremental solving has been enabled via bitwuzla_set_option().
 *
 * @note Assumptions added via this bitwuzla_assume() are not affected by
 *       context level changes and are only valid until the next
 *       bitwuzla_check_sat() call, no matter at which level they were assumed.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param nlevels The number of context levels to push.
 *
 * @see bitwuzla_set_option
 */
void bitwuzla_push(Bitwuzla *bitwuzla, uint32_t nlevels);

/**
 * Pop context levels.
 *
 * Requires that incremental solving has been enabled via bitwuzla_set_option().
 *
 * @note Assumptions added via this bitwuzla_assume() are not affected by
 *       context level changes and are only valid until the next
 *       bitwuzla_check_sat() call, no matter at which level they were assumed.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param nlevels The number of context levels to pop.
 *
 * @see bitwuzla_set_option
 */
void bitwuzla_pop(Bitwuzla *bitwuzla, uint32_t nlevels);

/**
 * Assert formula.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param term The formula to assert.
 */
void bitwuzla_assert(Bitwuzla *bitwuzla, const BitwuzlaTerm *term);

/**
 * Assume formula.
 *
 * Requires that incremental solving has been enabled via bitwuzla_set_option().
 *
 * @note Assumptions added via this function are not affected by context level
 *       changes and are only valid until the next bitwuzla_check_sat() call,
 *       no matter at which level they were assumed.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param term The formula to assume.
 *
 * @see bitwuzla_set_option
 * @see bitwuzla_is_unsat_assumption
 * @see bitwuzla_get_unsat_assumptions
 */
void bitwuzla_assume(Bitwuzla *bitwuzla, const BitwuzlaTerm *term);

/**
 * Determine if an assumption is an unsat assumption.
 *
 * Unsat assumptions are assumptions that force an input formula to become
 * unsatisfiable. Unsat assumptions handling in Boolector is analogous to
 * failed assumptions in MiniSAT.
 *
 * Requires that incremental solving has been enabled via bitwuzla_set_option().
 *
 * Requires that the last bitwuzla_check_sat() query returned BITWUZLA_UNSAT.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param term The assumption to check for.
 *
 * @return True if given assumption is an unsat assumption.
 *
 * @see bitwuzla_set_option
 * @see bitwuzla_assume
 * @see bitwuzla_check_sat
 */
bool bitwuzla_is_unsat_assumption(Bitwuzla *bitwuzla, const BitwuzlaTerm *term);

/**
 * Get the set of unsat assumptions.
 *
 * Unsat assumptions are assumptions that force an input formula to become
 * unsatisfiable. Unsat assumptions handling in Boolector is analogous to
 * failed assumptions in MiniSAT.
 *
 * Requires that incremental solving has been enabled via bitwuzla_set_option().
 *
 * Requires that the last bitwuzla_check_sat() query returned BITWUZLA_UNSAT.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param size Output parameter, stores the size of the returned array.
 *
 * @return An array with unsat assumptions of size \p size.
 *
 * @see bitwuzla_set_option
 * @see bitwuzla_assume
 * @see bitwuzla_check_sat
 */
BitwuzlaTerm **bitwuzla_get_unsat_assumptions(Bitwuzla *bitwuzla, size_t *size);

/**
 * Get the set unsat core (unsat assertions).
 *
 * The unsat core consists of the set of assertions that force an input formula
 * to become unsatisfiable.
 *
 * Requires that the last bitwuzla_check_sat() query returned BITWUZLA_UNSAT.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param size Output parameter, stores the size of the returned array.
 *
 * @return An array with unsat assertions of size \p size.
 *
 * @see bitwuzla_assert
 * @see bitwuzla_check_sat
 */
BitwuzlaTerm **bitwuzla_get_unsat_core(Bitwuzla *bitwuzla, size_t *size);

/**
 * Assert all added assumptions.
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @see bitwuzla_assume
 */
void bitwuzla_fixate_assumptions(Bitwuzla *bitwuzla);

/**
 * Reset all added assumptions.
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @see bitwuzla_assume
 */
void bitwuzla_reset_assumptions(Bitwuzla *bitwuzla);

/**
 * Simplify the current input formula.
 *
 * @note Assumptions are not considered for simplification.
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @return BITWUZLA_SAT if the input formula was simplified to true,
 *         BITWUZLA_UNSAT if it was simplified to false, and BITWUZLA_UNKNOWN
 *         otherwise.
 *
 * @see bitwuzla_assert
 * @see BitwuzlaResult
 */
BitwuzlaResult bitwuzla_simplify(Bitwuzla *bitwuzla);

/**
 * Check satisfiability of current input formula.
 *
 * An input formula consists of assertions added via bitwuzla_assert().  You
 * can guide the search for a solution by making assumptions via
 * bitwuzla_assume().
 *
 * @note Assertions and assumptions are combined via Boolean and.  Multiple
 *       calls to this function require enabling incremental solving via
 *       bitwuzla_set_option().
 *
 * @param bitwuzla The Bitwuzla instance.
 *
 * @return BITWUZLA_SAT if the input formula is satisfiable and BITWUZLA_UNSAT
 *         if it is unsatisfiable, and BITWUZLA_UNKNOWN when neither
 *         satisfiability nor unsatisfiability was determined. This can happen
 *         when \p bitwuzla was terminated via a termination callback.
 *
 * @see bitwuzla_assert
 * @see bitwuzla_assume
 * @see bitwuzla_set_option
 * @see BitwuzlaResult
 */
BitwuzlaResult bitwuzla_check_sat(Bitwuzla *bitwuzla);

/**
 * Get a term representing the model value of a given term.
 *
 * Requires that the last bitwuzla_check_sat() query returned BITWUZLA_SAT.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param term The term to query a model value for.
 *
 * @return A term representing the model value of term \p term.
 *
 * @see bitwuzla_check_sat
 */
BitwuzlaTerm *bitwuzla_get_value(Bitwuzla *bitwuzla, const BitwuzlaTerm *term);

/**
 * Print a model for the current input formula.
 *
 * Requires that the last bitwuzla_check_sat() query returned BITWUZLA_SAT.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param format The output format for printing the model. Either "btor" for
 *               the BTOR format, or "smt2" for the SMT-LIB v2 format.
 * @param file The file to print the model to.
 *
 * @see bitwuzla_check_sat
 */
void bitwuzla_print_model(Bitwuzla *bitwuzla, const char *format, FILE *file);

/**
 * Print the current input formula.
 *
 * Requires that incremental solving is not enabled.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param format The output format for printing the formula. Either "aiger_ascii"
 *               for the AIGER ascii format, "aiger_binary" for the binary
 *               AIGER format, "btor" for the BTOR format, or "smt2" for the
 *               SMT-LIB v2 format.
 * @param file The file to print the formula to.
 */
void bitwuzla_dump_formula(Bitwuzla *bitwuzla, const char *format, FILE *file);

/**
 * Parse input file.
 *
 * The format of the input file is auto detected.  
 * Requires that no terms have been created yet.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param infile The input file.
 * @param infile_name The name of the input file.
 * @param outfile The output file.
 * @param error_msg Output parameter, stores an error message in case a parse
 *                  error occurred, else \c NULL.
 * @param parsed_status Output parameter, stores the status of the input in case
 *                      of SMT-LIB v2 input, if given.
 * @param parsed_smt2 Output parameter, true if parsed input file has been
 *                    detected as SMT-LIB v2 input.
 *
 * @return BITWUZLA_SAT if the input formula was simplified to true,
 *         BITWUZLA_UNSAT if it was simplified to false, and BITWUZLA_UNKNOWN
 *         otherwise.
 *
 * @see bitwuzla_parse_format
 */
BitwuzlaResult bitwuzla_parse(Bitwuzla *bitwuzla,
                              FILE *infile,
                              const char *infile_name,
                              FILE *outfile,
                              char **error_msg,
                              BitwuzlaResult *parsed_status,
                              bool *parsed_smt2);

/**
 * Parse input file, assumed to be given in the specified format.
 *
 * Requires that no terms have been created yet.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param format The input format for printing the model. Either "btor" for
 *               the BTOR format, "btor2" for the BTOR2 format, or "smt2" for
 *               the SMT-LIB v2 format.
 * @param infile The input file.
 * @param infile_name The name of the input file.
 * @param outfile The output file.
 * @param error_msg Output parameter, stores an error message in case a parse
 *                  error occurred, else \c NULL.
 * @param parsed_status Output parameter, stores the status of the input in case
 *                      of SMT-LIB v2 input, if given.
 *
 * @return BITWUZLA_SAT if the input formula was simplified to true,
 *         BITWUZLA_UNSAT if it was simplified to false, and BITWUZLA_UNKNOWN
 *         otherwise.
 *
 * @see bitwuzla_parse
 */
BitwuzlaResult bitwuzla_parse_format(Bitwuzla *bitwuzla,
                                     const char *format,
                                     FILE *infile,
                                     const char *infile_name,
                                     FILE *outfile,
                                     char **error_msg,
                                     BitwuzlaResult *parsed_status);

/**
 * Substitute a set of keys with their corresponding values in the given term.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param term The term in which the keys are to be substituted.
 * @param map_size The size of the substitution map.
 * @param map_keys The keys.
 * @param map_values The mapped values.
 *
 * @return The resulting term from this substitution.
 */
BitwuzlaTerm *bitwuzla_substitute_term(Bitwuzla *bitwuzla,
                                       const BitwuzlaTerm *term,
                                       size_t map_size,
                                       BitwuzlaTerm *map_keys[],
                                       BitwuzlaTerm *map_values[]);

/**
 * Substitute a set of keys with their corresponding values in the set of given
 * terms.
 *
 * The terms in \p terms are replaced with the terms resulting from this
 * substitutions.
 *
 * @param bitwuzla The Bitwuzla instance.
 * @param terms_size The size of the set of terms.
 * @param terms The terms in which the keys are to be substituted.
 * @param map_size The size of the substitution map.
 * @param map_keys The keys.
 * @param map_values The mapped values.
 */
void bitwuzla_substitute_terms(Bitwuzla *bitwuzla,
                               size_t terms_size,
                               BitwuzlaTerm *terms[],
                               size_t map_size,
                               BitwuzlaTerm *map_keys[],
                               BitwuzlaTerm *map_values[]);

/* -------------------------------------------------------------------------- */
/* BitwuzlaSort                                                               */
/* -------------------------------------------------------------------------- */

/**
 * Compute the hash value for a sort.
 *
 * @param sort The sort.
 *
 * @return The hash value of the sort.
 */
size_t bitwuzla_sort_hash(const BitwuzlaSort *sort);

/**
 * Get the size of a bit-vector sort.
 *
 * Requires that given sort is a bit-vector sort.
 *
 * @param sort The sort.
 *
 * @return The size of the bit-vector sort.
 */
uint32_t bitwuzla_sort_bv_get_size(const BitwuzlaSort *sort);

/**
 * Get the exponent size of a floating-point sort.
 *
 * Requires that given sort is a floating-point sort.
 *
 * @param sort The sort.
 *
 * @return The exponent size of the floating-point sort.
 */
uint32_t bitwuzla_sort_fp_get_exp_size(const BitwuzlaSort *sort);

/**
 * Get the significand size of a floating-point sort.
 *
 * Requires that given sort is a floating-point sort.
 *
 * @param sort The sort.
 *
 * @return The significand size of the floating-point sort.
 */
uint32_t bitwuzla_sort_fp_get_sig_size(const BitwuzlaSort *sort);

/**
 * Get the index sort of an array sort.
 *
 * Requires that given sort is an array sort.
 *
 * @param sort The sort.
 *
 * @return The index sort of the array sort.
 */
BitwuzlaSort *bitwuzla_sort_array_get_index(const BitwuzlaSort *sort);

/**
 * Get the element sort of an array sort.
 *
 * Requires that given sort is an array sort.
 *
 * @param sort The sort.
 *
 * @return The element sort of the array sort.
 */
BitwuzlaSort *bitwuzla_sort_array_get_element(const BitwuzlaSort *sort);

/**
 * Get the domain sorts of a function sort, wrapped into a single sort.
 *
 * Requires that given sort is a function sort.
 *
 * @note The returned sort is a tuple sort consisting of the domain sorts of
 *       the given function sort. Tuple sorts are internal only and cannot be
 *       created via the Api.
 *
 * @param sort The sort.
 *
 * @return The domain sorts of the function sort.
 */
BitwuzlaSort *bitwuzla_sort_fun_get_domain(const BitwuzlaSort *sort);

/**
 * Get the domain sorts of a function sort.
 *
 * The domain sorts are returned as a \c NULL terminated array of sorts.  
 * Requires that given sort is a function sort.
 *
 * @param sort The sort.
 *
 * @return The domain sorts of the function sort as a \c NULL terminated array.
 */
BitwuzlaSort **bitwuzla_sort_fun_get_domain_sorts(const BitwuzlaSort *sort);

/**
 * Get the codomain sort of a function sort.
 *
 * Requires that given sort is a function sort.
 *
 * @param sort The sort.
 *
 * @return The codomain sort of the function sort.
 */
BitwuzlaSort *bitwuzla_sort_fun_get_codomain(const BitwuzlaSort *sort);

/**
 * Get the arity of a function sort.
 *
 * @param sort The sort.
 *
 * @return The number of arguments of the function sort.
 */
uint32_t bitwuzla_sort_fun_get_arity(const BitwuzlaSort *sort);

/**
 * Determine if two sorts are equal.
 *
 * @param sort0 The first sort.
 * @param sort1 The second sort.
 *
 * @return True if the given sorts are equal.
 */
bool bitwuzla_sort_is_equal(const BitwuzlaSort *sort0,
                            const BitwuzlaSort *sort1);

/**
 * Determine if a sort is an array sort.
 *
 * @param sort The sort.
 *
 * @return True if \p sort is an array sort.
 */
bool bitwuzla_sort_is_array(const BitwuzlaSort *sort);

/**
 * Determine if a sort is a bit-vector sort.
 *
 * @param sort The sort.
 *
 * @return True if \p sort is a bit-vector sort.
 */
bool bitwuzla_sort_is_bv(const BitwuzlaSort *sort);

/**
 * Determine if a sort is a floating-point sort.
 *
 * @param sort The sort.
 *
 * @return True if \p sort is a floating-point sort.
 */
bool bitwuzla_sort_is_fp(const BitwuzlaSort *sort);

/**
 * Determine if a sort is a function sort.
 *
 * @param sort The sort.
 *
 * @return True if \p sort is a function sort.
 */
bool bitwuzla_sort_is_fun(const BitwuzlaSort *sort);

/**
 * Determine if a sort is a roundingmode sort.
 *
 * @param sort The sort.
 *
 * @return True if \p sort is a roundingmode sort.
 */
bool bitwuzla_sort_is_rm(const BitwuzlaSort *sort);

/* -------------------------------------------------------------------------- */
/* BitwuzlaTerm                                                               */
/* -------------------------------------------------------------------------- */

/**
 * Compute the hash value for a term.
 *
 * @param term The term.
 *
 * @return The hash value of the term.
 */
size_t bitwuzla_term_hash(const BitwuzlaTerm *term);

/**
 * Get the kind of a term.
 *
 * @param term The term.
 *
 * @return The kind of the given term.
 *
 * @see BitwuzlaKind
 */
BitwuzlaKind bitwuzla_term_get_kind(const BitwuzlaTerm *term);

/**
 * Get the child terms of a term.
 *
 * Returns \c NULL if given term does not have children.
 *
 * @param term The term.
 * @param size Output parameter, stores the number of children of \p term.
 *
 * @return The children of \p term as an array of terms.
 */
BitwuzlaTerm **bitwuzla_term_get_children(const BitwuzlaTerm *term,
                                          size_t *size);

/**
 * Get the indices of an indexed term.
 *
 * Requires that given term is an indexed term.
 *
 * @param term The term.
 * @param size Output parameter, stores the number of indices of \p term.
 *
 * @return The children of \p term as an array of terms.
 */
uint32_t *bitwuzla_term_get_indices(const BitwuzlaTerm *term, size_t *size);

/**
 * Determine if a term is an indexed term.
 *
 * @param term The term.
 *
 * @return True if \p term is an indexed term.
 */
bool bitwuzla_term_is_indexed(const BitwuzlaTerm *term);

/**
 * Get the associated Bitwuzla instance of a term.
 *
 * @param term The term.
 *
 * @return The associated Bitwuzla instance.
 */
Bitwuzla *bitwuzla_term_get_bitwuzla(const BitwuzlaTerm *term);

/**
 * Get the sort of a term.
 *
 * @param term The term.
 *
 * @return The sort of the term.
 */
BitwuzlaSort *bitwuzla_term_get_sort(const BitwuzlaTerm *term);

/**
 * Get the index sort of an array term.
 *
 * Requires that given term is an array or an array store term.
 *
 * @param term The term.
 *
 * @return The index sort of the array term.
 */
BitwuzlaSort *bitwuzla_term_array_get_index_sort(const BitwuzlaTerm *term);

/**
 * Get the element sort of an array term.
 *
 * Requires that given term is an array or an array store term.
 *
 * @param term The term.
 *
 * @return The element sort of the array term.
 */
BitwuzlaSort *bitwuzla_term_array_get_element_sort(const BitwuzlaTerm *term);

/**
 * Get the domain sorts of a function term, wrapped into a single sort.
 *
 * Requires that given term is an uninterpreted function, a lambda term, a
 * store term, or an ite term over function terms.
 *
 * @note The returned sort is a tuple sort consisting of the domain sorts of
 *       the given function sort. Tuple sorts are internal only and cannot be
 *       created via the Api.
 *
 * @param term The term.
 *
 * @return The domain sorts of the function term.
 */
BitwuzlaSort *bitwuzla_term_fun_get_domain_sort(const BitwuzlaTerm *term);

/**
 * Get the domain sorts of a function term.
 *
 * The domain sorts are returned as a \c NULL terminated array of sorts.  
 * Requires that given term is an uninterpreted function, a lambda term, an
 * array store term, or an ite term over function terms.
 *
 * @param term The term.
 *
 * @return The domain sorts of the function term as a \c NULL terminated array.
 */
BitwuzlaSort **bitwuzla_term_fun_get_domain_sorts(const BitwuzlaTerm *term);

/**
 * Get the codomain sort of a function term.
 *
 * Requires that given term is an uninterpreted function, a lambda term, an
 * array store term, or an ite term over function terms.
 *
 * @param term The term.
 *
 * @return The codomain sort of the function term.
 */
BitwuzlaSort *bitwuzla_term_fun_get_codomain_sort(const BitwuzlaTerm *term);

/**
 * Get the bit-width of a bit-vector term.
 *
 * Requires that given term is a bit-vector term.
 *
 * @param term The term.
 *
 * @return The bit-width of the bit-vector term.
 */
uint32_t bitwuzla_term_bv_get_size(const BitwuzlaTerm *term);

/**
 * Get the bit-width of the exponent of a floating-point term.
 *
 * Requires that given term is a floating-point term.
 *
 * @param term The term.
 *
 * @return The bit-width of the exponent of the floating-point term.
 */
uint32_t bitwuzla_term_fp_get_exp_size(const BitwuzlaTerm *term);

/**
 * Get the bit-width of the significand of a floating-point term.
 *
 * Requires that given term is a floating-point term.
 *
 * @param term The term.
 *
 * @return The bit-width of the significand of the floating-point term.
 */
uint32_t bitwuzla_term_fp_get_sig_size(const BitwuzlaTerm *term);

/**
 * Get the arity of a function term.
 *
 * Requires that given term is a function term.
 *
 * @param term The term.
 *
 * @return The arity of the function term.
 */
uint32_t bitwuzla_term_fun_get_arity(const BitwuzlaTerm *term);

/**
 * Get the symbol of a term.
 *
 * @param term The term.
 *
 * @return The symbol of \p term. \c NULL if no symbol is defined.
 */
const char *bitwuzla_term_get_symbol(const BitwuzlaTerm *term);

/**
 * Set the symbol of a term.
 *
 * @param term The term.
 * @param symbol The symbol.
 */
void bitwuzla_term_set_symbol(BitwuzlaTerm *term, const char *symbol);

/**
 * Determine if the sorts of two terms are equal.
 *
 * @param term0 The first term.
 * @param term1 The second term.
 *
 * @return True if the sorts of \p term0 and \p term1 are equal.
 */
bool bitwuzla_term_is_equal_sort(const BitwuzlaTerm *term0,
                                 const BitwuzlaTerm *term1);

/**
 * Determine if a term is an array term.
 *
 * @param term The term.
 *
 * @return True if \p term is an array term.
 */
bool bitwuzla_term_is_array(const BitwuzlaTerm *term);

/**
 * Determine if a term is a constant.
 *
 * @param term The term.
 *
 * @return True if \p term is a constant.
 */
bool bitwuzla_term_is_const(const BitwuzlaTerm *term);

/**
 * Determine if a term is a function.
 *
 * @param term The term.
 *
 * @return True if \p term is a function.
 */
bool bitwuzla_term_is_fun(const BitwuzlaTerm *term);

/**
 * Determine if a term is a variable.
 *
 * @param term The term.
 *
 * @return True if \p term is a variable.
 */
bool bitwuzla_term_is_var(const BitwuzlaTerm *term);

/**
 * Determine if a term is a bound variable.
 *
 * @param term The term.
 *
 * @return True if \p term is a variable and bound.
 */
bool bitwuzla_term_is_bound_var(const BitwuzlaTerm *term);

/**
 * Determine if a term is a value.
 *
 * @param term The term.
 *
 * @return True if \p term is a value.
 */
bool bitwuzla_term_is_value(const BitwuzlaTerm *term);

/**
 * Determine if a term is a bit-vector value.
 *
 * @param term The term.
 *
 * @return True if \p term is a bit-vector value.
 */
bool bitwuzla_term_is_bv_value(const BitwuzlaTerm *term);

/**
 * Determine if a term is a floating-point value.
 *
 * @param term The term.
 *
 * @return True if \p term is a floating-point value.
 */
bool bitwuzla_term_is_fp_value(const BitwuzlaTerm *term);

/**
 * Determine if a term is a roundingmode value.
 *
 * @param term The term.
 *
 * @return True if \p term is a roundingmode value.
 */
bool bitwuzla_term_is_rm_value(const BitwuzlaTerm *term);

/**
 * Determine if a term is a bit-vector term.
 *
 * @param term The term.
 *
 * @return True if \p term is a bit-vector term.
 */
bool bitwuzla_term_is_bv(const BitwuzlaTerm *term);

/**
 * Determine if a term is a floating-point term.
 *
 * @param term The term.
 *
 * @return True if \p term is a floating-point term.
 */
bool bitwuzla_term_is_fp(const BitwuzlaTerm *term);

/**
 * Determine if a term is a roundingmode term.
 *
 * @param term The term.
 *
 * @return True if \p term is a roundingmode term.
 */
bool bitwuzla_term_is_rm(const BitwuzlaTerm *term);

/**
 * Determine if a term is a bit-vector value representing zero.
 *
 * @param term The term.
 *
 * @return True if \p term is a bit-vector zero value.
 */
bool bitwuzla_term_is_bv_value_zero(const BitwuzlaTerm *term);

/**
 * Determine if a term is a bit-vector value representing one.
 *
 * @param term The term.
 *
 * @return True if \p term is a bit-vector one value.
 */
bool bitwuzla_term_is_bv_value_one(const BitwuzlaTerm *term);

/**
 * Determine if a term is a bit-vector value with all bits set to one.
 *
 * @param term The term.
 *
 * @return True if \p term is a bit-vector value with all bits set to one.
 */
bool bitwuzla_term_is_bv_value_ones(const BitwuzlaTerm *term);

/**
 * Determine if a term is a bit-vector minimum signed value.
 *
 * @param term The term.
 *
 * @return True if \p term is a bit-vector value with the most significant bit
 *         set to 1 and all other bits set to 0.
 */
bool bitwuzla_term_is_bv_value_min_signed(const BitwuzlaTerm *term);

/**
 * Determine if a term is a bit-vector maximum signed value.
 *
 * @param term The term.
 *
 * @return True if \p term is a bit-vector value with the most significant bit
 *         set to 0 and all other bits set to 1.
 */
bool bitwuzla_term_is_bv_value_max_signed(const BitwuzlaTerm *term);

/**
 * Determine if a term is a floating-point positive zero (+zero) value.
 *
 * @param term The term.
 *
 * @return True if \p term is a floating-point +zero value.
 */
bool bitwuzla_term_is_fp_value_pos_zero(const BitwuzlaTerm *term);

/**
 * Determine if a term is a floating-point value negative zero (-zero).
 *
 * @param term The term.
 *
 * @return True if \p term is a floating-point value negative zero.
 */
bool bitwuzla_term_is_fp_value_neg_zero(const BitwuzlaTerm *term);

/**
 * Determine if a term is a floating-point positive infinity (+oo) value.
 *
 * @param term The term.
 *
 * @return True if \p term is a floating-point +oo value.
 */
bool bitwuzla_term_is_fp_value_pos_inf(const BitwuzlaTerm *term);

/**
 * Determine if a term is a floating-point negative infinity (-oo) value.
 *
 * @param term The term.
 *
 * @return True if \p term is a floating-point -oo value.
 */
bool bitwuzla_term_is_fp_value_neg_inf(const BitwuzlaTerm *term);

/**
 * Determine if a term is a floating-point NaN value.
 *
 * @param term The term.
 *
 * @return True if \p term is a floating-point NaN value.
 */
bool bitwuzla_term_is_fp_value_nan(const BitwuzlaTerm *term);

/**
 * Determine if a term is a constant array.
 *
 * @param term The term.
 *
 * @return True if \p term is a constant array.
 */
bool bitwuzla_term_is_const_array(const BitwuzlaTerm *term);

/**
 * Print term .
 *
 * @param term The term.
 * @param format The output format for printing the term. Either "btor" for the
 *               BTOR format, or "smt2" for the SMT-LIB v2 format.
 * @param file The file to print the term to.
 */
void bitwuzla_term_dump(const BitwuzlaTerm *term,
                        const char *format,
                        FILE *file);

/* -------------------------------------------------------------------------- */

#if __cplusplus
}
#endif

/* -------------------------------------------------------------------------- */
#endif

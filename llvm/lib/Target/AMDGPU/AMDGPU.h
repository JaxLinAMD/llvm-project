//===-- AMDGPU.h - MachineFunction passes hw codegen --------------*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// Modifications Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
// Notified per clause 4(b) of the license.
//
/// \file
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_AMDGPU_AMDGPU_H
#define LLVM_LIB_TARGET_AMDGPU_AMDGPU_H

#include "llvm/IR/IntrinsicsAMDGPU.h" // TODO: Sink this.
#include "llvm/IR/IntrinsicsR600.h"   // TODO: Sink this.
#include "llvm/IR/PassManager.h"
#include "llvm/Support/CodeGen.h"

namespace llvm {

class AMDGPUTargetMachine;
class FunctionPass;
class GCNTargetMachine;
class ImmutablePass;
class ModulePass;
class Pass;
class Target;
class TargetMachine;
class TargetOptions;
class PassRegistry;
class Module;

// GlobalISel passes
void initializeAMDGPUPreLegalizerCombinerPass(PassRegistry &);
FunctionPass *createAMDGPUPreLegalizeCombiner(bool IsOptNone);
void initializeAMDGPUPostLegalizerCombinerPass(PassRegistry &);
FunctionPass *createAMDGPUPostLegalizeCombiner(bool IsOptNone);
FunctionPass *createAMDGPURegBankCombiner(bool IsOptNone);
void initializeAMDGPURegBankCombinerPass(PassRegistry &);

// R600 Passes
FunctionPass *createR600VectorRegMerger();
FunctionPass *createR600ExpandSpecialInstrsPass();
FunctionPass *createR600EmitClauseMarkers();
FunctionPass *createR600ClauseMergePass();
FunctionPass *createR600Packetizer();
FunctionPass *createR600ControlFlowFinalizer();
FunctionPass *createAMDGPUCFGStructurizerPass();
FunctionPass *createR600ISelDag(TargetMachine *TM, CodeGenOpt::Level OptLevel);

// SI Passes
FunctionPass *createGCNDPPCombinePass();
FunctionPass *createSIAnnotateControlFlowPass();
FunctionPass *createSIFoldOperandsPass();
FunctionPass *createSIPeepholeSDWAPass();
FunctionPass *createSILowerI1CopiesPass();
FunctionPass *createSIAddIMGInitPass();
FunctionPass *createSIShrinkInstructionsPass();
FunctionPass *createSILoadStoreOptimizerPass();
FunctionPass *createSIWholeQuadModePass();
FunctionPass *createSIFixControlFlowLiveIntervalsPass();
FunctionPass *createSIOptimizeExecMaskingPreRAPass();
FunctionPass *createSIFixSGPRCopiesPass();
FunctionPass *createSIBufMemMergePass();
FunctionPass *createSIMemoryLegalizerPass();
FunctionPass *createSIInsertScratchBoundsPass();
FunctionPass *createSIFixScratchSizePass();
FunctionPass *createSIInsertWaitcntsPass();
FunctionPass *createSIInsertWaterfallPass();
FunctionPass *createSIPreAllocateWWMRegsPass();
FunctionPass *createSIFormMemoryClausesPass();

FunctionPass *createSIPostRABundlerPass();
FunctionPass *createAMDGPUSimplifyLibCallsPass(const TargetMachine *);
FunctionPass *createAMDGPUUseNativeCallsPass();
FunctionPass *createAMDGPUCodeGenPreparePass();
FunctionPass *createAMDGPULateCodeGenPreparePass();
FunctionPass *createAMDGPUMachineCFGStructurizerPass();
FunctionPass *createAMDGPUPropagateAttributesEarlyPass(const TargetMachine *);
ModulePass *createAMDGPUPropagateAttributesLatePass(const TargetMachine *);
FunctionPass *createAMDGPURewriteOutArgumentsPass();
FunctionPass *createSIModeRegisterPass();

struct AMDGPUSimplifyLibCallsPass : PassInfoMixin<AMDGPUSimplifyLibCallsPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

struct AMDGPUUseNativeCallsPass : PassInfoMixin<AMDGPUUseNativeCallsPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

void initializeAMDGPUDAGToDAGISelPass(PassRegistry&);

void initializeAMDGPUMachineCFGStructurizerPass(PassRegistry&);
extern char &AMDGPUMachineCFGStructurizerID;

void initializeAMDGPUAlwaysInlinePass(PassRegistry&);

Pass *createAMDGPUAnnotateKernelFeaturesPass();
void initializeAMDGPUAnnotateKernelFeaturesPass(PassRegistry &);
extern char &AMDGPUAnnotateKernelFeaturesID;

FunctionPass *createAMDGPUAtomicOptimizerPass();
void initializeAMDGPUAtomicOptimizerPass(PassRegistry &);
extern char &AMDGPUAtomicOptimizerID;

FunctionPass *createAMDGPUConditionalDiscardPass();
void initializeAMDGPUConditionalDiscardPass(PassRegistry &);
extern char &AMDGPUConditionalDiscardID;

ModulePass *createAMDGPULowerIntrinsicsPass();
void initializeAMDGPULowerIntrinsicsPass(PassRegistry &);
extern char &AMDGPULowerIntrinsicsID;

ModulePass *createAMDGPUFixFunctionBitcastsPass();
void initializeAMDGPUFixFunctionBitcastsPass(PassRegistry &);
extern char &AMDGPUFixFunctionBitcastsID;

FunctionPass *createAMDGPULowerKernelArgumentsPass();
void initializeAMDGPULowerKernelArgumentsPass(PassRegistry &);
extern char &AMDGPULowerKernelArgumentsID;

ModulePass *createAMDGPULowerKernelAttributesPass();
void initializeAMDGPULowerKernelAttributesPass(PassRegistry &);
extern char &AMDGPULowerKernelAttributesID;

struct AMDGPULowerKernelAttributesPass
    : PassInfoMixin<AMDGPULowerKernelAttributesPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

void initializeAMDGPUPropagateAttributesEarlyPass(PassRegistry &);
extern char &AMDGPUPropagateAttributesEarlyID;

void initializeAMDGPUPropagateAttributesLatePass(PassRegistry &);
extern char &AMDGPUPropagateAttributesLateID;

void initializeAMDGPURewriteOutArgumentsPass(PassRegistry &);
extern char &AMDGPURewriteOutArgumentsID;

void initializeGCNDPPCombinePass(PassRegistry &);
extern char &GCNDPPCombineID;

void initializeR600ClauseMergePassPass(PassRegistry &);
extern char &R600ClauseMergePassID;

void initializeR600ControlFlowFinalizerPass(PassRegistry &);
extern char &R600ControlFlowFinalizerID;

void initializeR600ExpandSpecialInstrsPassPass(PassRegistry &);
extern char &R600ExpandSpecialInstrsPassID;

void initializeR600VectorRegMergerPass(PassRegistry &);
extern char &R600VectorRegMergerID;

void initializeR600PacketizerPass(PassRegistry &);
extern char &R600PacketizerID;

void initializeSIFoldOperandsPass(PassRegistry &);
extern char &SIFoldOperandsID;

void initializeSIPeepholeSDWAPass(PassRegistry &);
extern char &SIPeepholeSDWAID;

void initializeSIShrinkInstructionsPass(PassRegistry&);
extern char &SIShrinkInstructionsID;

void initializeSIFixSGPRCopiesPass(PassRegistry &);
extern char &SIFixSGPRCopiesID;

void initializeSIFixVGPRCopiesPass(PassRegistry &);
extern char &SIFixVGPRCopiesID;

void initializeSILowerI1CopiesPass(PassRegistry &);
extern char &SILowerI1CopiesID;

void initializeSILowerSGPRSpillsPass(PassRegistry &);
extern char &SILowerSGPRSpillsID;

void initializeSILoadStoreOptimizerPass(PassRegistry &);
extern char &SILoadStoreOptimizerID;

void initializeSIBufMemMergePass(PassRegistry &);
extern char &SIBufMemMergeID;
  

void initializeSIWholeQuadModePass(PassRegistry &);
extern char &SIWholeQuadModeID;

void initializeSILowerControlFlowPass(PassRegistry &);
extern char &SILowerControlFlowID;

void initializeSIInsertScratchBoundsPass(PassRegistry &);
extern char &SIInsertScratchBoundsID;

void initializeSIFixScratchSizePass(PassRegistry &);
extern char &SIFixScratchSizeID;
extern const char *const SIScratchSizeSymbol;

void initializeSIRemoveShortExecBranchesPass(PassRegistry &);
extern char &SIRemoveShortExecBranchesID;

void initializeSIPreEmitPeepholePass(PassRegistry &);
extern char &SIPreEmitPeepholeID;

void initializeSIInsertSkipsPass(PassRegistry &);
extern char &SIInsertSkipsPassID;

void initializeSIOptimizeExecMaskingPass(PassRegistry &);
extern char &SIOptimizeExecMaskingID;

void initializeSIInsertWaterfallPass(PassRegistry &);
extern char &SIInsertWaterfallID;

void initializeSIPreAllocateWWMRegsPass(PassRegistry &);
extern char &SIPreAllocateWWMRegsID;

void initializeAMDGPUSimplifyLibCallsPass(PassRegistry &);
extern char &AMDGPUSimplifyLibCallsID;

void initializeAMDGPUUseNativeCallsPass(PassRegistry &);
extern char &AMDGPUUseNativeCallsID;

void initializeSIAddIMGInitPass(PassRegistry &);
extern char &SIAddIMGInitID;

void initializeAMDGPUPerfHintAnalysisPass(PassRegistry &);
extern char &AMDGPUPerfHintAnalysisID;

void initializeAMDGPURegPressAnalysisPass(PassRegistry &);
extern char &AMDGPURegPressAnalysisID;

// Passes common to R600 and SI
FunctionPass *createAMDGPUPromoteAlloca();
void initializeAMDGPUPromoteAllocaPass(PassRegistry&);
extern char &AMDGPUPromoteAllocaID;

FunctionPass *createAMDGPUPromoteAllocaToVector();
void initializeAMDGPUPromoteAllocaToVectorPass(PassRegistry&);
extern char &AMDGPUPromoteAllocaToVectorID;

struct AMDGPUPromoteAllocaPass : PassInfoMixin<AMDGPUPromoteAllocaPass> {
  AMDGPUPromoteAllocaPass(TargetMachine &TM) : TM(TM) {}
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

private:
  TargetMachine &TM;
};

struct AMDGPUPromoteAllocaToVectorPass
    : PassInfoMixin<AMDGPUPromoteAllocaToVectorPass> {
  AMDGPUPromoteAllocaToVectorPass(TargetMachine &TM) : TM(TM) {}
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);

private:
  TargetMachine &TM;
};

Pass *createAMDGPUStructurizeCFGPass();
FunctionPass *createAMDGPUISelDag(
  TargetMachine *TM = nullptr,
  CodeGenOpt::Level OptLevel = CodeGenOpt::Default);
ModulePass *createAMDGPUAlwaysInlinePass(bool GlobalOpt = true);
ModulePass *createR600OpenCLImageTypeLoweringPass();
FunctionPass *createAMDGPUAnnotateUniformValues();

ModulePass *createAMDGPUPrintfRuntimeBinding();
void initializeAMDGPUPrintfRuntimeBindingPass(PassRegistry&);
extern char &AMDGPUPrintfRuntimeBindingID;

ModulePass* createAMDGPUUnifyMetadataPass();
void initializeAMDGPUUnifyMetadataPass(PassRegistry&);
extern char &AMDGPUUnifyMetadataID;

void initializeSIOptimizeExecMaskingPreRAPass(PassRegistry&);
extern char &SIOptimizeExecMaskingPreRAID;

void initializeAMDGPUAnnotateUniformValuesPass(PassRegistry&);
extern char &AMDGPUAnnotateUniformValuesPassID;

void initializeAMDGPUCodeGenPreparePass(PassRegistry&);
extern char &AMDGPUCodeGenPrepareID;

void initializeAMDGPULateCodeGenPreparePass(PassRegistry &);
extern char &AMDGPULateCodeGenPrepareID;

void initializeSIAnnotateControlFlowPass(PassRegistry&);
extern char &SIAnnotateControlFlowPassID;

void initializeSIMemoryLegalizerPass(PassRegistry&);
extern char &SIMemoryLegalizerID;

void initializeSIModeRegisterPass(PassRegistry&);
extern char &SIModeRegisterID;

void initializeSIInsertHardClausesPass(PassRegistry &);
extern char &SIInsertHardClausesID;

void initializeSIInsertWaitcntsPass(PassRegistry&);
extern char &SIInsertWaitcntsID;

void initializeSIFormMemoryClausesPass(PassRegistry&);
extern char &SIFormMemoryClausesID;

void initializeSIPostRABundlerPass(PassRegistry&);
extern char &SIPostRABundlerID;

void initializeAMDGPUUnifyDivergentExitNodesPass(PassRegistry&);
extern char &AMDGPUUnifyDivergentExitNodesID;

ImmutablePass *createAMDGPUAAWrapperPass();
void initializeAMDGPUAAWrapperPassPass(PassRegistry&);
ImmutablePass *createAMDGPUExternalAAWrapperPass();
void initializeAMDGPUExternalAAWrapperPass(PassRegistry&);

void initializeAMDGPUArgumentUsageInfoPass(PassRegistry &);

Pass *createAMDGPUFunctionInliningPass();
void initializeAMDGPUInlinerPass(PassRegistry&);

ModulePass *createAMDGPUOpenCLEnqueuedBlockLoweringPass();
void initializeAMDGPUOpenCLEnqueuedBlockLoweringPass(PassRegistry &);
extern char &AMDGPUOpenCLEnqueuedBlockLoweringID;

void initializeGCNRegBankReassignPass(PassRegistry &);
extern char &GCNRegBankReassignID;

void initializeGCNNSAReassignPass(PassRegistry &);
extern char &GCNNSAReassignID;

namespace AMDGPU {
enum TargetIndex {
  TI_CONSTDATA_START,
  TI_SCRATCH_RSRC_DWORD0,
  TI_SCRATCH_RSRC_DWORD1,
  TI_SCRATCH_RSRC_DWORD2,
  TI_SCRATCH_RSRC_DWORD3
};
}

/// OpenCL uses address spaces to differentiate between
/// various memory regions on the hardware. On the CPU
/// all of the address spaces point to the same memory,
/// however on the GPU, each address space points to
/// a separate piece of memory that is unique from other
/// memory locations.
namespace AMDGPUAS {
  enum : unsigned {
    // The maximum value for flat, generic, local, private, constant and region.
    MAX_AMDGPU_ADDRESS = 7,

    FLAT_ADDRESS = 0,     ///< Address space for flat memory.
    GLOBAL_ADDRESS = 1,   ///< Address space for global memory (RAT0, VTX0).
    REGION_ADDRESS = 2,   ///< Address space for region memory. (GDS)

    CONSTANT_ADDRESS = 4, ///< Address space for constant memory (VTX2).
    LOCAL_ADDRESS = 3,    ///< Address space for local memory.
    PRIVATE_ADDRESS = 5,  ///< Address space for private memory.

    CONSTANT_ADDRESS_32BIT = 6, ///< Address space for 32-bit constant memory.

    BUFFER_FAT_POINTER = 7, ///< Address space for 160-bit buffer fat pointers.

    /// Address space for direct addressible parameter memory (CONST0).
    PARAM_D_ADDRESS = 6,
    /// Address space for indirect addressible parameter memory (VTX1).
    PARAM_I_ADDRESS = 7,

    // Do not re-order the CONSTANT_BUFFER_* enums.  Several places depend on
    // this order to be able to dynamically index a constant buffer, for
    // example:
    //
    // ConstantBufferAS = CONSTANT_BUFFER_0 + CBIdx

    CONSTANT_BUFFER_0 = 8,
    CONSTANT_BUFFER_1 = 9,
    CONSTANT_BUFFER_2 = 10,
    CONSTANT_BUFFER_3 = 11,
    CONSTANT_BUFFER_4 = 12,
    CONSTANT_BUFFER_5 = 13,
    CONSTANT_BUFFER_6 = 14,
    CONSTANT_BUFFER_7 = 15,
    CONSTANT_BUFFER_8 = 16,
    CONSTANT_BUFFER_9 = 17,
    CONSTANT_BUFFER_10 = 18,
    CONSTANT_BUFFER_11 = 19,
    CONSTANT_BUFFER_12 = 20,
    CONSTANT_BUFFER_13 = 21,
    CONSTANT_BUFFER_14 = 22,
    CONSTANT_BUFFER_15 = 23,

    // Some places use this if the address space can't be determined.
    UNKNOWN_ADDRESS_SPACE = ~0u,
  };
}

namespace AMDGPU {

// FIXME: Missing constant_32bit
inline bool isFlatGlobalAddrSpace(unsigned AS) {
  return AS == AMDGPUAS::GLOBAL_ADDRESS ||
         AS == AMDGPUAS::FLAT_ADDRESS ||
         AS == AMDGPUAS::CONSTANT_ADDRESS ||
         AS > AMDGPUAS::MAX_AMDGPU_ADDRESS;
}
}

} // End namespace llvm

#endif

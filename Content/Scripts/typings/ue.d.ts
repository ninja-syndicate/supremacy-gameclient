/// <reference path="_part_0_ue.d.ts">/>
/// <reference path="_part_1_ue.d.ts">/>
/// <reference path="_part_2_ue.d.ts">/>
/// <reference path="_part_3_ue.d.ts">/>
/// <reference path="_part_4_ue.d.ts">/>
declare class AudioCapture extends AudioGenerator { 
	static Load(ResourceName: string): AudioCapture;
	static Find(Outer: UObject, ResourceName: string): AudioCapture;
	static GetDefaultObject(): AudioCapture;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioCapture;
	StopCapturingAudio(): void;
	StartCapturingAudio(): void;
	IsCapturingAudio(): boolean;
	GetAudioCaptureDeviceInfo(OutInfo?: AudioCaptureDeviceInfo): {OutInfo: AudioCaptureDeviceInfo, $: boolean};
	static C(Other: UObject | any): AudioCapture;
}

declare class AudioCaptureFunctionLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): AudioCaptureFunctionLibrary;
	static Find(Outer: UObject, ResourceName: string): AudioCaptureFunctionLibrary;
	static GetDefaultObject(): AudioCaptureFunctionLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioCaptureFunctionLibrary;
	static CreateAudioCapture(): AudioCapture;
	static C(Other: UObject | any): AudioCaptureFunctionLibrary;
}

declare class AudioCaptureBlueprintLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): AudioCaptureBlueprintLibrary;
	static Find(Outer: UObject, ResourceName: string): AudioCaptureBlueprintLibrary;
	static GetDefaultObject(): AudioCaptureBlueprintLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioCaptureBlueprintLibrary;
	static Conv_AudioInputDeviceInfoToString(Info: AudioInputDeviceInfo): string;
	static C(Other: UObject | any): AudioCaptureBlueprintLibrary;
}

declare class AudioCaptureComponent extends SynthComponent { 
	JitterLatencyFrames: number;
	static Load(ResourceName: string): AudioCaptureComponent;
	static Find(Outer: UObject, ResourceName: string): AudioCaptureComponent;
	static GetDefaultObject(): AudioCaptureComponent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioCaptureComponent;
	static C(Other: UObject | any): AudioCaptureComponent;
}

declare class OnAudioInputDevicesObtained__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnAudioInputDevicesObtained__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnAudioInputDevicesObtained__PythonCallable;
	static GetDefaultObject(): OnAudioInputDevicesObtained__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnAudioInputDevicesObtained__PythonCallable;
	static C(Other: UObject | any): OnAudioInputDevicesObtained__PythonCallable;
}

declare class ArchVisCharacter extends Character { 
	LookUpAxisName: string;
	LookUpAtRateAxisName: string;
	TurnAxisName: string;
	TurnAtRateAxisName: string;
	MoveForwardAxisName: string;
	MoveRightAxisName: string;
	MouseSensitivityScale_Pitch: number;
	MouseSensitivityScale_Yaw: number;
	static GetDefaultObject(): ArchVisCharacter;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ArchVisCharacter;
	static C(Other: UObject | any): ArchVisCharacter;
}

declare class ArchVisCharMovementComponent extends CharacterMovementComponent { 
	RotationalAcceleration: Rotator;
	RotationalDeceleration: Rotator;
	MaxRotationalVelocity: Rotator;
	MinPitch: number;
	MaxPitch: number;
	WalkingFriction: number;
	WalkingSpeed: number;
	WalkingAcceleration: number;
	static Load(ResourceName: string): ArchVisCharMovementComponent;
	static Find(Outer: UObject, ResourceName: string): ArchVisCharMovementComponent;
	static GetDefaultObject(): ArchVisCharMovementComponent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ArchVisCharMovementComponent;
	static C(Other: UObject | any): ArchVisCharMovementComponent;
}

declare class CableComponent extends MeshComponent { 
	bAttachStart: boolean;
	bAttachEnd: boolean;
	AttachEndTo: ComponentReference;
	AttachEndToSocketName: string;
	EndLocation: Vector;
	CableLength: number;
	NumSegments: number;
	SubstepTime: number;
	SolverIterations: number;
	bEnableStiffness: boolean;
	bUseSubstepping: boolean;
	bSkipCableUpdateWhenNotVisible: boolean;
	bSkipCableUpdateWhenNotOwnerRecentlyRendered: boolean;
	bEnableCollision: boolean;
	CollisionFriction: number;
	CableForce: Vector;
	CableGravityScale: number;
	CableWidth: number;
	NumSides: number;
	TileMaterial: number;
	static Load(ResourceName: string): CableComponent;
	static Find(Outer: UObject, ResourceName: string): CableComponent;
	static GetDefaultObject(): CableComponent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): CableComponent;
	SetAttachEndToComponent(Component: SceneComponent,SocketName: string): void;
	SetAttachEndTo(Actor: Actor,ComponentProperty: string,SocketName: string): void;
	GetCableParticleLocations(Locations?: Vector[]): {Locations: Vector[]};
	GetAttachedComponent(): SceneComponent;
	GetAttachedActor(): Actor;
	static C(Other: UObject | any): CableComponent;
}

declare class CableActor extends Actor { 
	CableComponent: CableComponent;
	static GetDefaultObject(): CableActor;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): CableActor;
	static C(Other: UObject | any): CableActor;
}

declare type ECollectionScriptingShareType = 'Local' | 'Private' | 'Shared' | 'ECollectionScriptingShareType_MAX';
declare var ECollectionScriptingShareType : { Local:'Local',Private:'Private',Shared:'Shared',ECollectionScriptingShareType_MAX:'ECollectionScriptingShareType_MAX', };
declare class AssetTagsSubsystem extends EngineSubsystem { 
	static Load(ResourceName: string): AssetTagsSubsystem;
	static Find(Outer: UObject, ResourceName: string): AssetTagsSubsystem;
	static GetDefaultObject(): AssetTagsSubsystem;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AssetTagsSubsystem;
	ReparentCollection(Name: string,NewParentName: string): boolean;
	RenameCollection(Name: string,NewName: string): boolean;
	RemoveAssetsFromCollection(Name: string,AssetPathNames: string[]): boolean;
	RemoveAssetPtrsFromCollection(Name: string,AssetPtrs: UObject[]): boolean;
	RemoveAssetPtrFromCollection(Name: string,AssetPtr: UObject): boolean;
	RemoveAssetFromCollection(Name: string,AssetPathName: string): boolean;
	RemoveAssetDatasFromCollection(Name: string,AssetDatas: AssetData[]): boolean;
	RemoveAssetDataFromCollection(Name: string,AssetData: AssetData): boolean;
	GetCollectionsContainingAssetPtr(AssetPtr: UObject): string[];
	GetCollectionsContainingAssetData(AssetData: AssetData): string[];
	GetCollectionsContainingAsset(AssetPathName: string): string[];
	GetCollections(): string[];
	GetAssetsInCollection(Name: string): AssetData[];
	EmptyCollection(Name: string): boolean;
	DestroyCollection(Name: string): boolean;
	CreateCollection(Name: string,ShareType: ECollectionScriptingShareType): boolean;
	CollectionExists(Name: string): boolean;
	AddAssetToCollection(Name: string,AssetPathName: string): boolean;
	AddAssetsToCollection(Name: string,AssetPathNames: string[]): boolean;
	AddAssetPtrToCollection(Name: string,AssetPtr: UObject): boolean;
	AddAssetPtrsToCollection(Name: string,AssetPtrs: UObject[]): boolean;
	AddAssetDataToCollection(Name: string,AssetData: AssetData): boolean;
	AddAssetDatasToCollection(Name: string,AssetDatas: AssetData[]): boolean;
	static C(Other: UObject | any): AssetTagsSubsystem;
}

declare class CustomMeshTriangle { 
	Vertex0: Vector;
	Vertex1: Vector;
	Vertex2: Vector;
	clone() : CustomMeshTriangle;
	static C(Other: UObject | any): CustomMeshTriangle;
}

declare class CustomMeshComponent extends MeshComponent { 
	static Load(ResourceName: string): CustomMeshComponent;
	static Find(Outer: UObject, ResourceName: string): CustomMeshComponent;
	static GetDefaultObject(): CustomMeshComponent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): CustomMeshComponent;
	SetCustomMeshTriangles(Triangles: CustomMeshTriangle[]): boolean;
	ClearCustomMeshTriangles(): void;
	AddCustomMeshTriangles(Triangles: CustomMeshTriangle[]): void;
	static C(Other: UObject | any): CustomMeshComponent;
}

declare class StaticMeshEditorModelingMode extends BaseLegacyWidgetEdMode { 
	static Load(ResourceName: string): StaticMeshEditorModelingMode;
	static Find(Outer: UObject, ResourceName: string): StaticMeshEditorModelingMode;
	static GetDefaultObject(): StaticMeshEditorModelingMode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): StaticMeshEditorModelingMode;
	static C(Other: UObject | any): StaticMeshEditorModelingMode;
}

declare class GroomActorFactory extends ActorFactory { 
	static Load(ResourceName: string): GroomActorFactory;
	static Find(Outer: UObject, ResourceName: string): GroomActorFactory;
	static GetDefaultObject(): GroomActorFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): GroomActorFactory;
	static C(Other: UObject | any): GroomActorFactory;
}

declare class GroomBindingFactory extends Factory { 
	static Load(ResourceName: string): GroomBindingFactory;
	static Find(Outer: UObject, ResourceName: string): GroomBindingFactory;
	static GetDefaultObject(): GroomBindingFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): GroomBindingFactory;
	static C(Other: UObject | any): GroomBindingFactory;
}

declare class GroomEditorMode extends BaseLegacyWidgetEdMode { 
	static Load(ResourceName: string): GroomEditorMode;
	static Find(Outer: UObject, ResourceName: string): GroomEditorMode;
	static GetDefaultObject(): GroomEditorMode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): GroomEditorMode;
	static C(Other: UObject | any): GroomEditorMode;
}

declare class GroomFactory extends Factory { 
	static Load(ResourceName: string): GroomFactory;
	static Find(Outer: UObject, ResourceName: string): GroomFactory;
	static GetDefaultObject(): GroomFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): GroomFactory;
	static C(Other: UObject | any): GroomFactory;
}

declare class HairStrandsFactory extends Factory { 
	static Load(ResourceName: string): HairStrandsFactory;
	static Find(Outer: UObject, ResourceName: string): HairStrandsFactory;
	static GetDefaultObject(): HairStrandsFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): HairStrandsFactory;
	static C(Other: UObject | any): HairStrandsFactory;
}

declare class ReimportGroomCacheFactory extends HairStrandsFactory { 
	static Load(ResourceName: string): ReimportGroomCacheFactory;
	static Find(Outer: UObject, ResourceName: string): ReimportGroomCacheFactory;
	static GetDefaultObject(): ReimportGroomCacheFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ReimportGroomCacheFactory;
	static C(Other: UObject | any): ReimportGroomCacheFactory;
}

declare class ReimportHairStrandsFactory extends HairStrandsFactory { 
	static Load(ResourceName: string): ReimportHairStrandsFactory;
	static Find(Outer: UObject, ResourceName: string): ReimportHairStrandsFactory;
	static GetDefaultObject(): ReimportHairStrandsFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ReimportHairStrandsFactory;
	static C(Other: UObject | any): ReimportHairStrandsFactory;
}

declare type EGooglePADErrorCode = 'AssetPack_NO_ERROR' | 'AssetPack_APP_UNAVAILABLE' | 'AssetPack_UNAVAILABLE' | 'AssetPack_INVALID_REQUEST' | 'AssetPack_DOWNLOAD_NOT_FOUND' | 'AssetPack_API_NOT_AVAILABLE' | 'AssetPack_NETWORK_ERROR' | 'AssetPack_ACCESS_DENIED' | 'AssetPack_INSUFFICIENT_STORAGE' | 'AssetPack_PLAY_STORE_NOT_FOUND' | 'AssetPack_NETWORK_UNRESTRICTED' | 'AssetPack_INTERNAL_ERROR' | 'AssetPack_INITIALIZATION_NEEDED' | 'AssetPack_INITIALIZATION_FAILED' | 'AssetPack_MAX';
declare var EGooglePADErrorCode : { AssetPack_NO_ERROR:'AssetPack_NO_ERROR',AssetPack_APP_UNAVAILABLE:'AssetPack_APP_UNAVAILABLE',AssetPack_UNAVAILABLE:'AssetPack_UNAVAILABLE',AssetPack_INVALID_REQUEST:'AssetPack_INVALID_REQUEST',AssetPack_DOWNLOAD_NOT_FOUND:'AssetPack_DOWNLOAD_NOT_FOUND',AssetPack_API_NOT_AVAILABLE:'AssetPack_API_NOT_AVAILABLE',AssetPack_NETWORK_ERROR:'AssetPack_NETWORK_ERROR',AssetPack_ACCESS_DENIED:'AssetPack_ACCESS_DENIED',AssetPack_INSUFFICIENT_STORAGE:'AssetPack_INSUFFICIENT_STORAGE',AssetPack_PLAY_STORE_NOT_FOUND:'AssetPack_PLAY_STORE_NOT_FOUND',AssetPack_NETWORK_UNRESTRICTED:'AssetPack_NETWORK_UNRESTRICTED',AssetPack_INTERNAL_ERROR:'AssetPack_INTERNAL_ERROR',AssetPack_INITIALIZATION_NEEDED:'AssetPack_INITIALIZATION_NEEDED',AssetPack_INITIALIZATION_FAILED:'AssetPack_INITIALIZATION_FAILED',AssetPack_MAX:'AssetPack_MAX', };
declare type EGooglePADStorageMethod = 'AssetPack_STORAGE_FILES' | 'AssetPack_STORAGE_APK' | 'AssetPack_STORAGE_UNKNOWN' | 'AssetPack_STORAGE_NOT_INSTALLED' | 'AssetPack_STORAGE_MAX';
declare var EGooglePADStorageMethod : { AssetPack_STORAGE_FILES:'AssetPack_STORAGE_FILES',AssetPack_STORAGE_APK:'AssetPack_STORAGE_APK',AssetPack_STORAGE_UNKNOWN:'AssetPack_STORAGE_UNKNOWN',AssetPack_STORAGE_NOT_INSTALLED:'AssetPack_STORAGE_NOT_INSTALLED',AssetPack_STORAGE_MAX:'AssetPack_STORAGE_MAX', };
declare type EGooglePADCellularDataConfirmStatus = 'AssetPack_CONFIRM_UNKNOWN' | 'AssetPack_CONFIRM_PENDING' | 'AssetPack_CONFIRM_USER_APPROVED' | 'AssetPack_CONFIRM_USER_CANCELED' | 'AssetPack_CONFIRM_MAX';
declare var EGooglePADCellularDataConfirmStatus : { AssetPack_CONFIRM_UNKNOWN:'AssetPack_CONFIRM_UNKNOWN',AssetPack_CONFIRM_PENDING:'AssetPack_CONFIRM_PENDING',AssetPack_CONFIRM_USER_APPROVED:'AssetPack_CONFIRM_USER_APPROVED',AssetPack_CONFIRM_USER_CANCELED:'AssetPack_CONFIRM_USER_CANCELED',AssetPack_CONFIRM_MAX:'AssetPack_CONFIRM_MAX', };
declare type EGooglePADDownloadStatus = 'AssetPack_UNKNOWN' | 'AssetPack_DOWNLOAD_PENDING' | 'AssetPack_DOWNLOADING' | 'AssetPack_TRANSFERRING' | 'AssetPack_DOWNLOAD_COMPLETED' | 'AssetPack_DOWNLOAD_FAILED' | 'AssetPack_DOWNLOAD_CANCELED' | 'AssetPack_WAITING_FOR_WIFI' | 'AssetPack_NOT_INSTALLED' | 'AssetPack_INFO_PENDING' | 'AssetPack_INFO_FAILED' | 'AssetPack_REMOVAL_PENDING' | 'AssetPack_REMOVAL_FAILED' | 'AssetPack_MAX';
declare var EGooglePADDownloadStatus : { AssetPack_UNKNOWN:'AssetPack_UNKNOWN',AssetPack_DOWNLOAD_PENDING:'AssetPack_DOWNLOAD_PENDING',AssetPack_DOWNLOADING:'AssetPack_DOWNLOADING',AssetPack_TRANSFERRING:'AssetPack_TRANSFERRING',AssetPack_DOWNLOAD_COMPLETED:'AssetPack_DOWNLOAD_COMPLETED',AssetPack_DOWNLOAD_FAILED:'AssetPack_DOWNLOAD_FAILED',AssetPack_DOWNLOAD_CANCELED:'AssetPack_DOWNLOAD_CANCELED',AssetPack_WAITING_FOR_WIFI:'AssetPack_WAITING_FOR_WIFI',AssetPack_NOT_INSTALLED:'AssetPack_NOT_INSTALLED',AssetPack_INFO_PENDING:'AssetPack_INFO_PENDING',AssetPack_INFO_FAILED:'AssetPack_INFO_FAILED',AssetPack_REMOVAL_PENDING:'AssetPack_REMOVAL_PENDING',AssetPack_REMOVAL_FAILED:'AssetPack_REMOVAL_FAILED',AssetPack_MAX:'AssetPack_MAX', };
declare class GooglePADFunctionLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): GooglePADFunctionLibrary;
	static Find(Outer: UObject, ResourceName: string): GooglePADFunctionLibrary;
	static GetDefaultObject(): GooglePADFunctionLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): GooglePADFunctionLibrary;
	static ShowCellularDataConfirmation(): EGooglePADErrorCode;
	static RequestRemoval(Name: string): EGooglePADErrorCode;
	static RequestInfo(AssetPacks: string[]): EGooglePADErrorCode;
	static RequestDownload(AssetPacks: string[]): EGooglePADErrorCode;
	static ReleaseDownloadState(State: number): void;
	static ReleaseAssetPackLocation(Location: number): void;
	static GetTotalBytesToDownload(State: number): number;
	static GetStorageMethod(Location: number): EGooglePADStorageMethod;
	static GetShowCellularDataConfirmationStatus(Status?: EGooglePADCellularDataConfirmStatus): {Status: EGooglePADCellularDataConfirmStatus, $: EGooglePADErrorCode};
	static GetDownloadStatus(State: number): EGooglePADDownloadStatus;
	static GetDownloadState(Name: string,State?: number): {State: number, $: EGooglePADErrorCode};
	static GetBytesDownloaded(State: number): number;
	static GetAssetsPath(Location: number): string;
	static GetAssetPackLocation(Name: string,Location?: number): {Location: number, $: EGooglePADErrorCode};
	static CancelDownload(AssetPacks: string[]): EGooglePADErrorCode;
	static C(Other: UObject | any): GooglePADFunctionLibrary;
}

declare class MovieSceneGeometryCacheParams { 
	GeometryCacheAsset: GeometryCache;
	FirstLoopStartFrameOffset: FrameNumber;
	StartFrameOffset: FrameNumber;
	EndFrameOffset: FrameNumber;
	PlayRate: number;
	bReverse: boolean;
	StartOffset: number;
	EndOffset: number;
	GeometryCache: SoftObjectPath;
	clone() : MovieSceneGeometryCacheParams;
	static C(Other: UObject | any): MovieSceneGeometryCacheParams;
}

declare class MovieSceneGeometryCacheSection extends MovieSceneSection { 
	Params: MovieSceneGeometryCacheParams;
	static Load(ResourceName: string): MovieSceneGeometryCacheSection;
	static Find(Outer: UObject, ResourceName: string): MovieSceneGeometryCacheSection;
	static GetDefaultObject(): MovieSceneGeometryCacheSection;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MovieSceneGeometryCacheSection;
	static C(Other: UObject | any): MovieSceneGeometryCacheSection;
}

declare class MovieSceneGeometryCacheTrack extends MovieSceneNameableTrack { 
	AnimationSections: MovieSceneSection[];
	static Load(ResourceName: string): MovieSceneGeometryCacheTrack;
	static Find(Outer: UObject, ResourceName: string): MovieSceneGeometryCacheTrack;
	static GetDefaultObject(): MovieSceneGeometryCacheTrack;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MovieSceneGeometryCacheTrack;
	static C(Other: UObject | any): MovieSceneGeometryCacheTrack;
}

declare class GeometryCacheStreamerSettings extends DeveloperSettings { 
	LookAheadBuffer: number;
	MaxMemoryAllowed: number;
	static Load(ResourceName: string): GeometryCacheStreamerSettings;
	static Find(Outer: UObject, ResourceName: string): GeometryCacheStreamerSettings;
	static GetDefaultObject(): GeometryCacheStreamerSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): GeometryCacheStreamerSettings;
	static C(Other: UObject | any): GeometryCacheStreamerSettings;
}

declare class OnDynamicMeshModifiedBP__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDynamicMeshModifiedBP__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDynamicMeshModifiedBP__PythonCallable;
	static GetDefaultObject(): OnDynamicMeshModifiedBP__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDynamicMeshModifiedBP__PythonCallable;
	static C(Other: UObject | any): OnDynamicMeshModifiedBP__PythonCallable;
}

declare class MobileInstalledContent extends UObject { 
	static Load(ResourceName: string): MobileInstalledContent;
	static Find(Outer: UObject, ResourceName: string): MobileInstalledContent;
	static GetDefaultObject(): MobileInstalledContent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MobileInstalledContent;
	Mount(PakOrder: number,MountPoint: string): boolean;
	GetInstalledContentSize(): number;
	GetDiskFreeSpace(): number;
	static C(Other: UObject | any): MobileInstalledContent;
}

declare class MobilePendingContent extends MobileInstalledContent { 
	static Load(ResourceName: string): MobilePendingContent;
	static Find(Outer: UObject, ResourceName: string): MobilePendingContent;
	static GetDefaultObject(): MobilePendingContent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MobilePendingContent;
	GetTotalDownloadedSize(): number;
	GetRequiredDiskSpace(): number;
	GetInstallProgress(): number;
	GetDownloadStatusText(): string;
	GetDownloadSpeed(): number;
	GetDownloadSize(): number;
	static C(Other: UObject | any): MobilePendingContent;
}

declare class MobilePatchingLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): MobilePatchingLibrary;
	static Find(Outer: UObject, ResourceName: string): MobilePatchingLibrary;
	static GetDefaultObject(): MobilePatchingLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MobilePatchingLibrary;
	static HasActiveWiFiConnection(): boolean;
	static GetSupportedPlatformNames(): string[];
	static GetInstalledContent(InstallDirectory: string): MobileInstalledContent;
	static GetActiveDeviceProfileName(): string;
	static C(Other: UObject | any): MobilePatchingLibrary;
}

declare class OnContentInstallFailed__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnContentInstallFailed__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnContentInstallFailed__PythonCallable;
	static GetDefaultObject(): OnContentInstallFailed__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnContentInstallFailed__PythonCallable;
	static C(Other: UObject | any): OnContentInstallFailed__PythonCallable;
}

declare class OnContentInstallSucceeded__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnContentInstallSucceeded__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnContentInstallSucceeded__PythonCallable;
	static GetDefaultObject(): OnContentInstallSucceeded__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnContentInstallSucceeded__PythonCallable;
	static C(Other: UObject | any): OnContentInstallSucceeded__PythonCallable;
}

declare class OnRequestContentFailed__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnRequestContentFailed__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnRequestContentFailed__PythonCallable;
	static GetDefaultObject(): OnRequestContentFailed__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnRequestContentFailed__PythonCallable;
	static C(Other: UObject | any): OnRequestContentFailed__PythonCallable;
}

declare class OnRequestContentSucceeded__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnRequestContentSucceeded__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnRequestContentSucceeded__PythonCallable;
	static GetDefaultObject(): OnRequestContentSucceeded__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnRequestContentSucceeded__PythonCallable;
	static C(Other: UObject | any): OnRequestContentSucceeded__PythonCallable;
}

declare class KismetProceduralMeshLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): KismetProceduralMeshLibrary;
	static Find(Outer: UObject, ResourceName: string): KismetProceduralMeshLibrary;
	static GetDefaultObject(): KismetProceduralMeshLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): KismetProceduralMeshLibrary;
	static SliceProceduralMesh(InProcMesh: ProceduralMeshComponent,PlanePosition: Vector,PlaneNormal: Vector,bCreateOtherHalf: boolean,OutOtherHalfProcMesh?: ProceduralMeshComponent,CapOption?: EProcMeshSliceCapOption,CapMaterial?: MaterialInterface): {OutOtherHalfProcMesh: ProceduralMeshComponent};
	static GetSectionFromStaticMesh(InMesh: StaticMesh,LODIndex: number,SectionIndex: number,Vertices?: Vector[],Triangles?: number[],Normals?: Vector[],UVs?: Vector2D[],Tangents?: ProcMeshTangent[]): {Vertices: Vector[], Triangles: number[], Normals: Vector[], UVs: Vector2D[], Tangents: ProcMeshTangent[]};
	static GetSectionFromProceduralMesh(InProcMesh: ProceduralMeshComponent,SectionIndex: number,Vertices?: Vector[],Triangles?: number[],Normals?: Vector[],UVs?: Vector2D[],Tangents?: ProcMeshTangent[]): {Vertices: Vector[], Triangles: number[], Normals: Vector[], UVs: Vector2D[], Tangents: ProcMeshTangent[]};
	static GenerateBoxMesh(BoxRadius: Vector,Vertices?: Vector[],Triangles?: number[],Normals?: Vector[],UVs?: Vector2D[],Tangents?: ProcMeshTangent[]): {Vertices: Vector[], Triangles: number[], Normals: Vector[], UVs: Vector2D[], Tangents: ProcMeshTangent[]};
	static CreateGridMeshWelded(NumX: number,NumY: number,Triangles?: number[],Vertices?: Vector[],UVs?: Vector2D[],GridSpacing?: number): {Triangles: number[], Vertices: Vector[], UVs: Vector2D[]};
	static CreateGridMeshTriangles(NumX: number,NumY: number,bWinding: boolean,Triangles?: number[]): {Triangles: number[]};
	static CreateGridMeshSplit(NumX: number,NumY: number,Triangles?: number[],Vertices?: Vector[],UVs?: Vector2D[],UV1s?: Vector2D[],GridSpacing?: number): {Triangles: number[], Vertices: Vector[], UVs: Vector2D[], UV1s: Vector2D[]};
	static CopyProceduralMeshFromStaticMeshComponent(StaticMeshComponent: StaticMeshComponent,LODIndex: number,ProcMeshComponent: ProceduralMeshComponent,bCreateCollision: boolean): void;
	static ConvertQuadToTriangles(Triangles?: number[],Vert0?: number,Vert1?: number,Vert2?: number,Vert3?: number): {Triangles: number[]};
	static CalculateTangentsForMesh(Vertices: Vector[],Triangles: number[],UVs: Vector2D[],Normals?: Vector[],Tangents?: ProcMeshTangent[]): {Normals: Vector[], Tangents: ProcMeshTangent[]};
	static C(Other: UObject | any): KismetProceduralMeshLibrary;
}

declare type EResonanceRenderMode = 'StereoPanning' | 'BinauralLowQuality' | 'BinauralMediumQuality' | 'BinauralHighQuality' | 'RoomEffectsOnly' | 'EResonanceRenderMode_MAX';
declare var EResonanceRenderMode : { StereoPanning:'StereoPanning',BinauralLowQuality:'BinauralLowQuality',BinauralMediumQuality:'BinauralMediumQuality',BinauralHighQuality:'BinauralHighQuality',RoomEffectsOnly:'RoomEffectsOnly',EResonanceRenderMode_MAX:'EResonanceRenderMode_MAX', };
declare class ResonanceAudioSoundfieldSettings extends SoundfieldEncodingSettingsBase { 
	RenderMode: EResonanceRenderMode;
	static Load(ResourceName: string): ResonanceAudioSoundfieldSettings;
	static Find(Outer: UObject, ResourceName: string): ResonanceAudioSoundfieldSettings;
	static GetDefaultObject(): ResonanceAudioSoundfieldSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ResonanceAudioSoundfieldSettings;
	static C(Other: UObject | any): ResonanceAudioSoundfieldSettings;
}

declare type ERaMaterialName = 'TRANSPARENT' | 'ACOUSTIC_CEILING_TILES' | 'BRICK_BARE' | 'BRICK_PAINTED' | 'CONCRETE_BLOCK_COARSE' | 'CONCRETE_BLOCK_PAINTED' | 'CURTAIN_HEAVY' | 'FIBER_GLASS_INSULATION' | 'GLASS_THIN' | 'GLASS_THICK' | 'GRASS' | 'LINOLEUM_ON_CONCRETE' | 'MARBLE' | 'METAL' | 'PARQUET_ONCONCRETE' | 'PLASTER_ROUGH' | 'PLASTER_SMOOTH' | 'PLYWOOD_PANEL' | 'POLISHED_CONCRETE_OR_TILE' | 'SHEETROCK' | 'WATER_OR_ICE_SURFACE' | 'WOOD_CEILING' | 'WOOD_PANEL' | 'UNIFORM' | 'ERaMaterialName_MAX';
declare var ERaMaterialName : { TRANSPARENT:'TRANSPARENT',ACOUSTIC_CEILING_TILES:'ACOUSTIC_CEILING_TILES',BRICK_BARE:'BRICK_BARE',BRICK_PAINTED:'BRICK_PAINTED',CONCRETE_BLOCK_COARSE:'CONCRETE_BLOCK_COARSE',CONCRETE_BLOCK_PAINTED:'CONCRETE_BLOCK_PAINTED',CURTAIN_HEAVY:'CURTAIN_HEAVY',FIBER_GLASS_INSULATION:'FIBER_GLASS_INSULATION',GLASS_THIN:'GLASS_THIN',GLASS_THICK:'GLASS_THICK',GRASS:'GRASS',LINOLEUM_ON_CONCRETE:'LINOLEUM_ON_CONCRETE',MARBLE:'MARBLE',METAL:'METAL',PARQUET_ONCONCRETE:'PARQUET_ONCONCRETE',PLASTER_ROUGH:'PLASTER_ROUGH',PLASTER_SMOOTH:'PLASTER_SMOOTH',PLYWOOD_PANEL:'PLYWOOD_PANEL',POLISHED_CONCRETE_OR_TILE:'POLISHED_CONCRETE_OR_TILE',SHEETROCK:'SHEETROCK',WATER_OR_ICE_SURFACE:'WATER_OR_ICE_SURFACE',WOOD_CEILING:'WOOD_CEILING',WOOD_PANEL:'WOOD_PANEL',UNIFORM:'UNIFORM',ERaMaterialName_MAX:'ERaMaterialName_MAX', };
declare class ResonanceAudioReverbPluginSettings { 
	bEnableRoomEffects: boolean;
	bGetTransformFromAudioVolume: boolean;
	RoomPosition: Vector;
	RoomRotation: Quat;
	RoomDimensions: Vector;
	LeftWallMaterial: ERaMaterialName;
	RightWallMaterial: ERaMaterialName;
	FloorMaterial: ERaMaterialName;
	CeilingMaterial: ERaMaterialName;
	FrontWallMaterial: ERaMaterialName;
	BackWallMaterial: ERaMaterialName;
	ReflectionScalar: number;
	ReverbGain: number;
	ReverbTimeModifier: number;
	ReverbBrightness: number;
	clone() : ResonanceAudioReverbPluginSettings;
	static C(Other: UObject | any): ResonanceAudioReverbPluginSettings;
}

declare class ResonanceAudioReverbPluginPreset extends SoundEffectSubmixPreset { 
	Settings: ResonanceAudioReverbPluginSettings;
	static Load(ResourceName: string): ResonanceAudioReverbPluginPreset;
	static Find(Outer: UObject, ResourceName: string): ResonanceAudioReverbPluginPreset;
	static GetDefaultObject(): ResonanceAudioReverbPluginPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ResonanceAudioReverbPluginPreset;
	SetRoomRotation(InRotation: Quat): void;
	SetRoomPosition(InPosition: Vector): void;
	SetRoomMaterials(InMaterials: ERaMaterialName[]): void;
	SetRoomDimensions(InDimensions: Vector): void;
	SetReverbTimeModifier(InReverbTimeModifier: number): void;
	SetReverbGain(InReverbGain: number): void;
	SetReverbBrightness(InReverbBrightness: number): void;
	SetReflectionScalar(InReflectionScalar: number): void;
	SetEnableRoomEffects(bInEnableRoomEffects: boolean): void;
	static C(Other: UObject | any): ResonanceAudioReverbPluginPreset;
	SetGlobalReverbPreset(): void;
	static SetGlobalReverbPreset(InPreset: ResonanceAudioReverbPluginPreset): void;
}

declare class ResonanceAudioBlueprintFunctionLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): ResonanceAudioBlueprintFunctionLibrary;
	static Find(Outer: UObject, ResourceName: string): ResonanceAudioBlueprintFunctionLibrary;
	static GetDefaultObject(): ResonanceAudioBlueprintFunctionLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ResonanceAudioBlueprintFunctionLibrary;
	static SetGlobalReverbPreset(InPreset: ResonanceAudioReverbPluginPreset): void;
	static GetGlobalReverbPreset(): ResonanceAudioReverbPluginPreset;
	static C(Other: UObject | any): ResonanceAudioBlueprintFunctionLibrary;
}

declare type ERaSpatializationMethod = 'STEREO_PANNING' | 'HRTF' | 'ERaSpatializationMethod_MAX';
declare var ERaSpatializationMethod : { STEREO_PANNING:'STEREO_PANNING',HRTF:'HRTF',ERaSpatializationMethod_MAX:'ERaSpatializationMethod_MAX', };
declare type ERaDistanceRolloffModel = 'LOGARITHMIC' | 'LINEAR' | 'NONE' | 'ERaDistanceRolloffModel_MAX';
declare var ERaDistanceRolloffModel : { LOGARITHMIC:'LOGARITHMIC',LINEAR:'LINEAR',NONE:'NONE',ERaDistanceRolloffModel_MAX:'ERaDistanceRolloffModel_MAX', };
declare class ResonanceAudioSpatializationSourceSettings extends SpatializationPluginSourceSettingsBase { 
	SpatializationMethod: ERaSpatializationMethod;
	Pattern: number;
	Sharpness: number;
	bToggleVisualization: boolean;
	Scale: number;
	Spread: number;
	Rolloff: ERaDistanceRolloffModel;
	MinDistance: number;
	MaxDistance: number;
	static Load(ResourceName: string): ResonanceAudioSpatializationSourceSettings;
	static Find(Outer: UObject, ResourceName: string): ResonanceAudioSpatializationSourceSettings;
	static GetDefaultObject(): ResonanceAudioSpatializationSourceSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ResonanceAudioSpatializationSourceSettings;
	SetSoundSourceSpread(InSpread: number): void;
	SetSoundSourceDirectivity(InPattern: number,InSharpness: number): void;
	static C(Other: UObject | any): ResonanceAudioSpatializationSourceSettings;
}

declare class ResonanceAudioDirectivityVisualizer extends Actor { 
	Material: Material;
	Settings: ResonanceAudioSpatializationSourceSettings;
	static GetDefaultObject(): ResonanceAudioDirectivityVisualizer;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ResonanceAudioDirectivityVisualizer;
	static C(Other: UObject | any): ResonanceAudioDirectivityVisualizer;
}

declare type ERaQualityMode = 'STEREO_PANNING' | 'BINAURAL_LOW' | 'BINAURAL_MEDIUM' | 'BINAURAL_HIGH' | 'ERaQualityMode_MAX';
declare var ERaQualityMode : { STEREO_PANNING:'STEREO_PANNING',BINAURAL_LOW:'BINAURAL_LOW',BINAURAL_MEDIUM:'BINAURAL_MEDIUM',BINAURAL_HIGH:'BINAURAL_HIGH',ERaQualityMode_MAX:'ERaQualityMode_MAX', };
declare class ResonanceAudioSettings extends UObject { 
	OutputSubmix: SoftObjectPath;
	QualityMode: ERaQualityMode;
	GlobalReverbPreset: SoftObjectPath;
	GlobalSourcePreset: SoftObjectPath;
	static Load(ResourceName: string): ResonanceAudioSettings;
	static Find(Outer: UObject, ResourceName: string): ResonanceAudioSettings;
	static GetDefaultObject(): ResonanceAudioSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ResonanceAudioSettings;
	static C(Other: UObject | any): ResonanceAudioSettings;
}

declare type ESynth1OscType = 'Sine' | 'Saw' | 'Triangle' | 'Square' | 'Noise' | 'Count' | 'ESynth1OscType_MAX';
declare var ESynth1OscType : { Sine:'Sine',Saw:'Saw',Triangle:'Triangle',Square:'Square',Noise:'Noise',Count:'Count',ESynth1OscType_MAX:'ESynth1OscType_MAX', };
declare type ESynthLFOType = 'Sine' | 'UpSaw' | 'DownSaw' | 'Square' | 'Triangle' | 'Exponential' | 'RandomSampleHold' | 'Count' | 'ESynthLFOType_MAX';
declare var ESynthLFOType : { Sine:'Sine',UpSaw:'UpSaw',DownSaw:'DownSaw',Square:'Square',Triangle:'Triangle',Exponential:'Exponential',RandomSampleHold:'RandomSampleHold',Count:'Count',ESynthLFOType_MAX:'ESynthLFOType_MAX', };
declare type ESynthLFOMode = 'Sync' | 'OneShot' | 'Free' | 'Count' | 'ESynthLFOMode_MAX';
declare var ESynthLFOMode : { Sync:'Sync',OneShot:'OneShot',Free:'Free',Count:'Count',ESynthLFOMode_MAX:'ESynthLFOMode_MAX', };
declare type ESynthLFOPatchType = 'PatchToNone' | 'PatchToGain' | 'PatchToOscFreq' | 'PatchToFilterFreq' | 'PatchToFilterQ' | 'PatchToOscPulseWidth' | 'PatchToOscPan' | 'PatchLFO1ToLFO2Frequency' | 'PatchLFO1ToLFO2Gain' | 'Count' | 'ESynthLFOPatchType_MAX';
declare var ESynthLFOPatchType : { PatchToNone:'PatchToNone',PatchToGain:'PatchToGain',PatchToOscFreq:'PatchToOscFreq',PatchToFilterFreq:'PatchToFilterFreq',PatchToFilterQ:'PatchToFilterQ',PatchToOscPulseWidth:'PatchToOscPulseWidth',PatchToOscPan:'PatchToOscPan',PatchLFO1ToLFO2Frequency:'PatchLFO1ToLFO2Frequency',PatchLFO1ToLFO2Gain:'PatchLFO1ToLFO2Gain',Count:'Count',ESynthLFOPatchType_MAX:'ESynthLFOPatchType_MAX', };
declare type ESynthModEnvPatch = 'PatchToNone' | 'PatchToOscFreq' | 'PatchToFilterFreq' | 'PatchToFilterQ' | 'PatchToLFO1Gain' | 'PatchToLFO2Gain' | 'PatchToLFO1Freq' | 'PatchToLFO2Freq' | 'Count' | 'ESynthModEnvPatch_MAX';
declare var ESynthModEnvPatch : { PatchToNone:'PatchToNone',PatchToOscFreq:'PatchToOscFreq',PatchToFilterFreq:'PatchToFilterFreq',PatchToFilterQ:'PatchToFilterQ',PatchToLFO1Gain:'PatchToLFO1Gain',PatchToLFO2Gain:'PatchToLFO2Gain',PatchToLFO1Freq:'PatchToLFO1Freq',PatchToLFO2Freq:'PatchToLFO2Freq',Count:'Count',ESynthModEnvPatch_MAX:'ESynthModEnvPatch_MAX', };
declare type ESynthModEnvBiasPatch = 'PatchToNone' | 'PatchToOscFreq' | 'PatchToFilterFreq' | 'PatchToFilterQ' | 'PatchToLFO1Gain' | 'PatchToLFO2Gain' | 'PatchToLFO1Freq' | 'PatchToLFO2Freq' | 'Count' | 'ESynthModEnvBiasPatch_MAX';
declare var ESynthModEnvBiasPatch : { PatchToNone:'PatchToNone',PatchToOscFreq:'PatchToOscFreq',PatchToFilterFreq:'PatchToFilterFreq',PatchToFilterQ:'PatchToFilterQ',PatchToLFO1Gain:'PatchToLFO1Gain',PatchToLFO2Gain:'PatchToLFO2Gain',PatchToLFO1Freq:'PatchToLFO1Freq',PatchToLFO2Freq:'PatchToLFO2Freq',Count:'Count',ESynthModEnvBiasPatch_MAX:'ESynthModEnvBiasPatch_MAX', };
declare type ESynthFilterType = 'LowPass' | 'HighPass' | 'BandPass' | 'BandStop' | 'Count' | 'ESynthFilterType_MAX';
declare var ESynthFilterType : { LowPass:'LowPass',HighPass:'HighPass',BandPass:'BandPass',BandStop:'BandStop',Count:'Count',ESynthFilterType_MAX:'ESynthFilterType_MAX', };
declare type ESynthFilterAlgorithm = 'OnePole' | 'StateVariable' | 'Ladder' | 'Count' | 'ESynthFilterAlgorithm_MAX';
declare var ESynthFilterAlgorithm : { OnePole:'OnePole',StateVariable:'StateVariable',Ladder:'Ladder',Count:'Count',ESynthFilterAlgorithm_MAX:'ESynthFilterAlgorithm_MAX', };
declare type ESynthStereoDelayMode = 'Normal' | 'Cross' | 'PingPong' | 'Count' | 'ESynthStereoDelayMode_MAX';
declare var ESynthStereoDelayMode : { Normal:'Normal',Cross:'Cross',PingPong:'PingPong',Count:'Count',ESynthStereoDelayMode_MAX:'ESynthStereoDelayMode_MAX', };
declare type ESynth1PatchSource = 'LFO1' | 'LFO2' | 'Envelope' | 'BiasEnvelope' | 'Count' | 'ESynth1PatchSource_MAX';
declare var ESynth1PatchSource : { LFO1:'LFO1',LFO2:'LFO2',Envelope:'Envelope',BiasEnvelope:'BiasEnvelope',Count:'Count',ESynth1PatchSource_MAX:'ESynth1PatchSource_MAX', };
declare type ESynth1PatchDestination = 'Osc1Gain' | 'Osc1Frequency' | 'Osc1Pulsewidth' | 'Osc2Gain' | 'Osc2Frequency' | 'Osc2Pulsewidth' | 'FilterFrequency' | 'FilterQ' | 'Gain' | 'Pan' | 'LFO1Frequency' | 'LFO1Gain' | 'LFO2Frequency' | 'LFO2Gain' | 'Count' | 'ESynth1PatchDestination_MAX';
declare var ESynth1PatchDestination : { Osc1Gain:'Osc1Gain',Osc1Frequency:'Osc1Frequency',Osc1Pulsewidth:'Osc1Pulsewidth',Osc2Gain:'Osc2Gain',Osc2Frequency:'Osc2Frequency',Osc2Pulsewidth:'Osc2Pulsewidth',FilterFrequency:'FilterFrequency',FilterQ:'FilterQ',Gain:'Gain',Pan:'Pan',LFO1Frequency:'LFO1Frequency',LFO1Gain:'LFO1Gain',LFO2Frequency:'LFO2Frequency',LFO2Gain:'LFO2Gain',Count:'Count',ESynth1PatchDestination_MAX:'ESynth1PatchDestination_MAX', };
declare class Synth1PatchCable { 
	Depth: number;
	Destination: ESynth1PatchDestination;
	clone() : Synth1PatchCable;
	static C(Other: UObject | any): Synth1PatchCable;
}

declare class EpicSynth1Patch { 
	PatchSource: ESynth1PatchSource;
	PatchCables: Synth1PatchCable[];
	clone() : EpicSynth1Patch;
	static C(Other: UObject | any): EpicSynth1Patch;
}

declare class ModularSynthPreset extends TableRowBase { 
	bEnablePolyphony: boolean;
	Osc1Type: ESynth1OscType;
	Osc1Gain: number;
	Osc1Octave: number;
	Osc1Semitones: number;
	Osc1Cents: number;
	Osc1PulseWidth: number;
	Osc2Type: ESynth1OscType;
	Osc2Gain: number;
	Osc2Octave: number;
	Osc2Semitones: number;
	Osc2Cents: number;
	Osc2PulseWidth: number;
	Portamento: number;
	bEnableUnison: boolean;
	bEnableOscillatorSync: boolean;
	Spread: number;
	Pan: number;
	LFO1Frequency: number;
	LFO1Gain: number;
	LFO1Type: ESynthLFOType;
	LFO1Mode: ESynthLFOMode;
	LFO1PatchType: ESynthLFOPatchType;
	LFO2Frequency: number;
	LFO2Gain: number;
	LFO2Type: ESynthLFOType;
	LFO2Mode: ESynthLFOMode;
	LFO2PatchType: ESynthLFOPatchType;
	GainDb: number;
	AttackTime: number;
	DecayTime: number;
	SustainGain: number;
	ReleaseTime: number;
	ModEnvPatchType: ESynthModEnvPatch;
	ModEnvBiasPatchType: ESynthModEnvBiasPatch;
	bInvertModulationEnvelope: boolean;
	bInvertModulationEnvelopeBias: boolean;
	ModulationEnvelopeDepth: number;
	ModulationEnvelopeAttackTime: number;
	ModulationEnvelopeDecayTime: number;
	ModulationEnvelopeSustainGain: number;
	ModulationEnvelopeReleaseTime: number;
	bLegato: boolean;
	bRetrigger: boolean;
	FilterFrequency: number;
	FilterQ: number;
	FilterType: ESynthFilterType;
	FilterAlgorithm: ESynthFilterAlgorithm;
	bStereoDelayEnabled: boolean;
	StereoDelayMode: ESynthStereoDelayMode;
	StereoDelayTime: number;
	StereoDelayFeedback: number;
	StereoDelayWetlevel: number;
	StereoDelayRatio: number;
	bChorusEnabled: boolean;
	ChorusDepth: number;
	ChorusFeedback: number;
	ChorusFrequency: number;
	Patches: EpicSynth1Patch[];
	clone() : ModularSynthPreset;
	static C(Other: UObject | any): ModularSynthPreset;
}

declare class ModularSynthPresetBankEntry { 
	PresetName: string;
	Preset: ModularSynthPreset;
	clone() : ModularSynthPresetBankEntry;
	static C(Other: UObject | any): ModularSynthPresetBankEntry;
}

declare class ModularSynthPresetBank extends UObject { 
	Presets: ModularSynthPresetBankEntry[];
	static Load(ResourceName: string): ModularSynthPresetBank;
	static Find(Outer: UObject, ResourceName: string): ModularSynthPresetBank;
	static GetDefaultObject(): ModularSynthPresetBank;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ModularSynthPresetBank;
	static C(Other: UObject | any): ModularSynthPresetBank;
	AddModularSynthPresetToBankAsset(Preset: ModularSynthPreset,PresetName: string): void;
	static AddModularSynthPresetToBankAsset(InBank: ModularSynthPresetBank,Preset: ModularSynthPreset,PresetName: string): void;
}

declare class ModularSynthLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): ModularSynthLibrary;
	static Find(Outer: UObject, ResourceName: string): ModularSynthLibrary;
	static GetDefaultObject(): ModularSynthLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ModularSynthLibrary;
	static AddModularSynthPresetToBankAsset(InBank: ModularSynthPresetBank,Preset: ModularSynthPreset,PresetName: string): void;
	static C(Other: UObject | any): ModularSynthLibrary;
}

declare class PatchId { 
	ID: number;
	clone() : PatchId;
	static C(Other: UObject | any): PatchId;
}

declare class ModularSynthComponent extends SynthComponent { 
	VoiceCount: number;
	static Load(ResourceName: string): ModularSynthComponent;
	static Find(Outer: UObject, ResourceName: string): ModularSynthComponent;
	static GetDefaultObject(): ModularSynthComponent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ModularSynthComponent;
	SetSynthPreset(SynthPreset: ModularSynthPreset): void;
	SetSustainGain(SustainGain: number): void;
	SetStereoDelayWetlevel(DelayWetlevel: number): void;
	SetStereoDelayTime(DelayTimeMsec: number): void;
	SetStereoDelayRatio(DelayRatio: number): void;
	SetStereoDelayMode(StereoDelayMode: ESynthStereoDelayMode): void;
	SetStereoDelayIsEnabled(StereoDelayEnabled: boolean): void;
	SetStereoDelayFeedback(DelayFeedback: number): void;
	SetSpread(Spread: number): void;
	SetReleaseTime(ReleaseTimeMsec: number): void;
	SetPortamento(Portamento: number): void;
	SetPitchBend(PitchBend: number): void;
	SetPan(Pan: number): void;
	SetOscType(OscIndex: number,OscType: ESynth1OscType): void;
	SetOscSync(bIsSynced: boolean): void;
	SetOscSemitones(OscIndex: number,Semitones: number): void;
	SetOscPulsewidth(OscIndex: number,Pulsewidth: number): void;
	SetOscOctave(OscIndex: number,Octave: number): void;
	SetOscGainMod(OscIndex: number,OscGainMod: number): void;
	SetOscGain(OscIndex: number,OscGain: number): void;
	SetOscFrequencyMod(OscIndex: number,OscFreqMod: number): void;
	SetOscCents(OscIndex: number,Cents: number): void;
	SetModEnvSustainGain(SustainGain: number): void;
	SetModEnvReleaseTime(Release: number): void;
	SetModEnvPatch(InPatchType: ESynthModEnvPatch): void;
	SetModEnvInvert(bInvert: boolean): void;
	SetModEnvDepth(Depth: number): void;
	SetModEnvDecayTime(DecayTimeMsec: number): void;
	SetModEnvBiasPatch(InPatchType: ESynthModEnvBiasPatch): void;
	SetModEnvBiasInvert(bInvert: boolean): void;
	SetModEnvAttackTime(AttackTimeMsec: number): void;
	SetLFOType(LFOIndex: number,LFOType: ESynthLFOType): void;
	SetLFOPatch(LFOIndex: number,LFOPatchType: ESynthLFOPatchType): void;
	SetLFOMode(LFOIndex: number,LFOMode: ESynthLFOMode): void;
	SetLFOGainMod(LFOIndex: number,GainMod: number): void;
	SetLFOGain(LFOIndex: number,Gain: number): void;
	SetLFOFrequencyMod(LFOIndex: number,FrequencyModHz: number): void;
	SetLFOFrequency(LFOIndex: number,FrequencyHz: number): void;
	SetGainDb(GainDb: number): void;
	SetFilterType(FilterType: ESynthFilterType): void;
	SetFilterQMod(FilterQ: number): void;
	SetFilterQ(FilterQ: number): void;
	SetFilterFrequencyMod(FilterFrequencyHz: number): void;
	SetFilterFrequency(FilterFrequencyHz: number): void;
	SetFilterAlgorithm(FilterAlgorithm: ESynthFilterAlgorithm): void;
	SetEnableUnison(EnableUnison: boolean): void;
	SetEnableRetrigger(RetriggerEnabled: boolean): void;
	SetEnablePolyphony(bEnablePolyphony: boolean): void;
	SetEnablePatch(PatchId: PatchId,bIsEnabled: boolean): boolean;
	SetEnableLegato(LegatoEnabled: boolean): void;
	SetDecayTime(DecayTimeMsec: number): void;
	SetChorusFrequency(Frequency: number): void;
	SetChorusFeedback(Feedback: number): void;
	SetChorusEnabled(EnableChorus: boolean): void;
	SetChorusDepth(Depth: number): void;
	SetAttackTime(AttackTimeMsec: number): void;
	NoteOn(Note: number,Velocity: number,Duration: number): void;
	NoteOff(Note: number,bAllNotesOff: boolean,bKillAllNotes: boolean): void;
	CreatePatch(PatchSource: ESynth1PatchSource,PatchCables: Synth1PatchCable[],bEnableByDefault: boolean): PatchId;
	static C(Other: UObject | any): ModularSynthComponent;
}

declare class SourceEffectBitCrusherSettings { 
	CrushedSampleRate: number;
	SampleRateModulation: SoundModulationDestinationSettings;
	CrushedBits: number;
	BitModulation: SoundModulationDestinationSettings;
	clone() : SourceEffectBitCrusherSettings;
	static C(Other: UObject | any): SourceEffectBitCrusherSettings;
}

declare class SourceEffectBitCrusherBaseSettings { 
	SampleRate: number;
	BitDepth: number;
	clone() : SourceEffectBitCrusherBaseSettings;
	static C(Other: UObject | any): SourceEffectBitCrusherBaseSettings;
}

declare class SourceEffectBitCrusherPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectBitCrusherSettings;
	static Load(ResourceName: string): SourceEffectBitCrusherPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectBitCrusherPreset;
	static GetDefaultObject(): SourceEffectBitCrusherPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectBitCrusherPreset;
	SetSettings(Settings: SourceEffectBitCrusherBaseSettings): void;
	SetSampleRateModulator(Modulator: SoundModulatorBase): void;
	SetSampleRate(SampleRate: number): void;
	SetModulationSettings(ModulationSettings: SourceEffectBitCrusherSettings): void;
	SetBits(Bits: number): void;
	SetBitModulator(Modulator: SoundModulatorBase): void;
	static C(Other: UObject | any): SourceEffectBitCrusherPreset;
}

declare class SourceEffectChorusSettings { 
	Depth: number;
	Frequency: number;
	Feedback: number;
	WetLevel: number;
	DryLevel: number;
	Spread: number;
	DepthModulation: SoundModulationDestinationSettings;
	FrequencyModulation: SoundModulationDestinationSettings;
	FeedbackModulation: SoundModulationDestinationSettings;
	WetModulation: SoundModulationDestinationSettings;
	DryModulation: SoundModulationDestinationSettings;
	SpreadModulation: SoundModulationDestinationSettings;
	clone() : SourceEffectChorusSettings;
	static C(Other: UObject | any): SourceEffectChorusSettings;
}

declare class SourceEffectChorusBaseSettings { 
	Depth: number;
	Frequency: number;
	Feedback: number;
	WetLevel: number;
	DryLevel: number;
	Spread: number;
	clone() : SourceEffectChorusBaseSettings;
	static C(Other: UObject | any): SourceEffectChorusBaseSettings;
}

declare class SourceEffectChorusPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectChorusSettings;
	static Load(ResourceName: string): SourceEffectChorusPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectChorusPreset;
	static GetDefaultObject(): SourceEffectChorusPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectChorusPreset;
	SetWetModulator(Modulator: SoundModulatorBase): void;
	SetWet(WetAmount: number): void;
	SetSpreadModulator(Modulator: SoundModulatorBase): void;
	SetSpread(Spread: number): void;
	SetSettings(Settings: SourceEffectChorusBaseSettings): void;
	SetModulationSettings(ModulationSettings: SourceEffectChorusSettings): void;
	SetFrequencyModulator(Modulator: SoundModulatorBase): void;
	SetFrequency(Frequency: number): void;
	SetFeedbackModulator(Modulator: SoundModulatorBase): void;
	SetFeedback(Feedback: number): void;
	SetDryModulator(Modulator: SoundModulatorBase): void;
	SetDry(DryAmount: number): void;
	SetDepthModulator(Modulator: SoundModulatorBase): void;
	SetDepth(Depth: number): void;
	static C(Other: UObject | any): SourceEffectChorusPreset;
}

declare type ESourceEffectDynamicsProcessorType = 'Compressor' | 'Limiter' | 'Expander' | 'Gate' | 'UpwardsCompressor' | 'Count' | 'ESourceEffectDynamicsProcessorType_MAX';
declare var ESourceEffectDynamicsProcessorType : { Compressor:'Compressor',Limiter:'Limiter',Expander:'Expander',Gate:'Gate',UpwardsCompressor:'UpwardsCompressor',Count:'Count',ESourceEffectDynamicsProcessorType_MAX:'ESourceEffectDynamicsProcessorType_MAX', };
declare type ESourceEffectDynamicsPeakMode = 'MeanSquared' | 'RootMeanSquared' | 'Peak' | 'Count' | 'ESourceEffectDynamicsPeakMode_MAX';
declare var ESourceEffectDynamicsPeakMode : { MeanSquared:'MeanSquared',RootMeanSquared:'RootMeanSquared',Peak:'Peak',Count:'Count',ESourceEffectDynamicsPeakMode_MAX:'ESourceEffectDynamicsPeakMode_MAX', };
declare class SourceEffectDynamicsProcessorSettings { 
	DynamicsProcessorType: ESourceEffectDynamicsProcessorType;
	PeakMode: ESourceEffectDynamicsPeakMode;
	LookAheadMsec: number;
	AttackTimeMsec: number;
	ReleaseTimeMsec: number;
	ThresholdDb: number;
	Ratio: number;
	KneeBandwidthDb: number;
	InputGainDb: number;
	OutputGainDb: number;
	bStereoLinked: boolean;
	bAnalogMode: boolean;
	clone() : SourceEffectDynamicsProcessorSettings;
	static C(Other: UObject | any): SourceEffectDynamicsProcessorSettings;
}

declare class SourceEffectDynamicsProcessorPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectDynamicsProcessorSettings;
	static Load(ResourceName: string): SourceEffectDynamicsProcessorPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectDynamicsProcessorPreset;
	static GetDefaultObject(): SourceEffectDynamicsProcessorPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectDynamicsProcessorPreset;
	SetSettings(InSettings: SourceEffectDynamicsProcessorSettings): void;
	static C(Other: UObject | any): SourceEffectDynamicsProcessorPreset;
}

declare class EnvelopeFollowerListener extends ActorComponent { 
	OnEnvelopeFollowerUpdate: UnrealEngineMulticastDelegate<(EnvelopeValue: number) => void>;
	static Load(ResourceName: string): EnvelopeFollowerListener;
	static Find(Outer: UObject, ResourceName: string): EnvelopeFollowerListener;
	static GetDefaultObject(): EnvelopeFollowerListener;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): EnvelopeFollowerListener;
	static C(Other: UObject | any): EnvelopeFollowerListener;
}

declare type EEnvelopeFollowerPeakMode = 'MeanSquared' | 'RootMeanSquared' | 'Peak' | 'Count' | 'EEnvelopeFollowerPeakMode_MAX';
declare var EEnvelopeFollowerPeakMode : { MeanSquared:'MeanSquared',RootMeanSquared:'RootMeanSquared',Peak:'Peak',Count:'Count',EEnvelopeFollowerPeakMode_MAX:'EEnvelopeFollowerPeakMode_MAX', };
declare class SourceEffectEnvelopeFollowerSettings { 
	AttackTime: number;
	ReleaseTime: number;
	PeakMode: EEnvelopeFollowerPeakMode;
	bIsAnalogMode: boolean;
	clone() : SourceEffectEnvelopeFollowerSettings;
	static C(Other: UObject | any): SourceEffectEnvelopeFollowerSettings;
}

declare class SourceEffectEnvelopeFollowerPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectEnvelopeFollowerSettings;
	static Load(ResourceName: string): SourceEffectEnvelopeFollowerPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectEnvelopeFollowerPreset;
	static GetDefaultObject(): SourceEffectEnvelopeFollowerPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectEnvelopeFollowerPreset;
	UnregisterEnvelopeFollowerListener(EnvelopeFollowerListener: EnvelopeFollowerListener): void;
	SetSettings(InSettings: SourceEffectEnvelopeFollowerSettings): void;
	RegisterEnvelopeFollowerListener(EnvelopeFollowerListener: EnvelopeFollowerListener): void;
	static C(Other: UObject | any): SourceEffectEnvelopeFollowerPreset;
}

declare class SourceEffectEQBand { 
	Frequency: number;
	Bandwidth: number;
	GainDb: number;
	bEnabled: boolean;
	clone() : SourceEffectEQBand;
	static C(Other: UObject | any): SourceEffectEQBand;
}

declare class SourceEffectEQSettings { 
	EQBands: SourceEffectEQBand[];
	clone() : SourceEffectEQSettings;
	static C(Other: UObject | any): SourceEffectEQSettings;
}

declare class SourceEffectEQPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectEQSettings;
	static Load(ResourceName: string): SourceEffectEQPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectEQPreset;
	static GetDefaultObject(): SourceEffectEQPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectEQPreset;
	SetSettings(InSettings: SourceEffectEQSettings): void;
	static C(Other: UObject | any): SourceEffectEQPreset;
}

declare type ESourceEffectFilterCircuit = 'OnePole' | 'StateVariable' | 'Ladder' | 'Count' | 'ESourceEffectFilterCircuit_MAX';
declare var ESourceEffectFilterCircuit : { OnePole:'OnePole',StateVariable:'StateVariable',Ladder:'Ladder',Count:'Count',ESourceEffectFilterCircuit_MAX:'ESourceEffectFilterCircuit_MAX', };
declare type ESourceEffectFilterType = 'LowPass' | 'HighPass' | 'BandPass' | 'BandStop' | 'Count' | 'ESourceEffectFilterType_MAX';
declare var ESourceEffectFilterType : { LowPass:'LowPass',HighPass:'HighPass',BandPass:'BandPass',BandStop:'BandStop',Count:'Count',ESourceEffectFilterType_MAX:'ESourceEffectFilterType_MAX', };
declare type ESourceEffectFilterParam = 'FilterFrequency' | 'FilterResonance' | 'Count' | 'ESourceEffectFilterParam_MAX';
declare var ESourceEffectFilterParam : { FilterFrequency:'FilterFrequency',FilterResonance:'FilterResonance',Count:'Count',ESourceEffectFilterParam_MAX:'ESourceEffectFilterParam_MAX', };
declare class SourceEffectFilterAudioBusModulationSettings { 
	AudioBus: AudioBus;
	EnvelopeFollowerAttackTimeMsec: number;
	EnvelopeFollowerReleaseTimeMsec: number;
	EnvelopeGainMultiplier: number;
	FilterParam: ESourceEffectFilterParam;
	MinFrequencyModulation: number;
	MaxFrequencyModulation: number;
	MinResonanceModulation: number;
	MaxResonanceModulation: number;
	clone() : SourceEffectFilterAudioBusModulationSettings;
	static C(Other: UObject | any): SourceEffectFilterAudioBusModulationSettings;
}

declare class SourceEffectFilterSettings { 
	FilterCircuit: ESourceEffectFilterCircuit;
	FilterType: ESourceEffectFilterType;
	CutoffFrequency: number;
	FilterQ: number;
	AudioBusModulation: SourceEffectFilterAudioBusModulationSettings[];
	clone() : SourceEffectFilterSettings;
	static C(Other: UObject | any): SourceEffectFilterSettings;
}

declare class SourceEffectFilterPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectFilterSettings;
	static Load(ResourceName: string): SourceEffectFilterPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectFilterPreset;
	static GetDefaultObject(): SourceEffectFilterPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectFilterPreset;
	SetSettings(InSettings: SourceEffectFilterSettings): void;
	static C(Other: UObject | any): SourceEffectFilterPreset;
}

declare class SourceEffectFoldbackDistortionSettings { 
	InputGainDb: number;
	ThresholdDb: number;
	OutputGainDb: number;
	clone() : SourceEffectFoldbackDistortionSettings;
	static C(Other: UObject | any): SourceEffectFoldbackDistortionSettings;
}

declare class SourceEffectFoldbackDistortionPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectFoldbackDistortionSettings;
	static Load(ResourceName: string): SourceEffectFoldbackDistortionPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectFoldbackDistortionPreset;
	static GetDefaultObject(): SourceEffectFoldbackDistortionPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectFoldbackDistortionPreset;
	SetSettings(InSettings: SourceEffectFoldbackDistortionSettings): void;
	static C(Other: UObject | any): SourceEffectFoldbackDistortionPreset;
}

declare type EStereoChannelMode = 'MidSide' | 'LeftRight' | 'count' | 'EStereoChannelMode_MAX';
declare var EStereoChannelMode : { MidSide:'MidSide',LeftRight:'LeftRight',count:'count',EStereoChannelMode_MAX:'EStereoChannelMode_MAX', };
declare class SourceEffectMidSideSpreaderSettings { 
	SpreadAmount: number;
	InputMode: EStereoChannelMode;
	OutputMode: EStereoChannelMode;
	bEqualPower: boolean;
	clone() : SourceEffectMidSideSpreaderSettings;
	static C(Other: UObject | any): SourceEffectMidSideSpreaderSettings;
}

declare class SourceEffectMidSideSpreaderPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectMidSideSpreaderSettings;
	static Load(ResourceName: string): SourceEffectMidSideSpreaderPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectMidSideSpreaderPreset;
	static GetDefaultObject(): SourceEffectMidSideSpreaderPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectMidSideSpreaderPreset;
	SetSettings(InSettings: SourceEffectMidSideSpreaderSettings): void;
	static C(Other: UObject | any): SourceEffectMidSideSpreaderPreset;
}

declare type ESourceEffectMotionFilterTopology = 'SerialMode' | 'ParallelMode' | 'Count' | 'ESourceEffectMotionFilterTopology_MAX';
declare var ESourceEffectMotionFilterTopology : { SerialMode:'SerialMode',ParallelMode:'ParallelMode',Count:'Count',ESourceEffectMotionFilterTopology_MAX:'ESourceEffectMotionFilterTopology_MAX', };
declare type ESourceEffectMotionFilterCircuit = 'OnePole' | 'StateVariable' | 'Ladder' | 'Count' | 'ESourceEffectMotionFilterCircuit_MAX';
declare var ESourceEffectMotionFilterCircuit : { OnePole:'OnePole',StateVariable:'StateVariable',Ladder:'Ladder',Count:'Count',ESourceEffectMotionFilterCircuit_MAX:'ESourceEffectMotionFilterCircuit_MAX', };
declare type ESourceEffectMotionFilterType = 'LowPass' | 'HighPass' | 'BandPass' | 'BandStop' | 'Count' | 'ESourceEffectMotionFilterType_MAX';
declare var ESourceEffectMotionFilterType : { LowPass:'LowPass',HighPass:'HighPass',BandPass:'BandPass',BandStop:'BandStop',Count:'Count',ESourceEffectMotionFilterType_MAX:'ESourceEffectMotionFilterType_MAX', };
declare class SourceEffectIndividualFilterSettings { 
	FilterCircuit: ESourceEffectMotionFilterCircuit;
	FilterType: ESourceEffectMotionFilterType;
	CutoffFrequency: number;
	FilterQ: number;
	clone() : SourceEffectIndividualFilterSettings;
	static C(Other: UObject | any): SourceEffectIndividualFilterSettings;
}

declare type ESourceEffectMotionFilterModDestination = 'FilterACutoffFrequency' | 'FilterAResonance' | 'FilterAOutputVolumeDB' | 'FilterBCutoffFrequency' | 'FilterBResonance' | 'FilterBOutputVolumeDB' | 'FilterMix' | 'Count' | 'ESourceEffectMotionFilterModDestination_MAX';
declare var ESourceEffectMotionFilterModDestination : { FilterACutoffFrequency:'FilterACutoffFrequency',FilterAResonance:'FilterAResonance',FilterAOutputVolumeDB:'FilterAOutputVolumeDB',FilterBCutoffFrequency:'FilterBCutoffFrequency',FilterBResonance:'FilterBResonance',FilterBOutputVolumeDB:'FilterBOutputVolumeDB',FilterMix:'FilterMix',Count:'Count',ESourceEffectMotionFilterModDestination_MAX:'ESourceEffectMotionFilterModDestination_MAX', };
declare type ESourceEffectMotionFilterModSource = 'DistanceFromListener' | 'SpeedRelativeToListener' | 'SpeedOfSourceEmitter' | 'SpeedOfListener' | 'SpeedOfAngleDelta' | 'Count' | 'ESourceEffectMotionFilterModSource_MAX';
declare var ESourceEffectMotionFilterModSource : { DistanceFromListener:'DistanceFromListener',SpeedRelativeToListener:'SpeedRelativeToListener',SpeedOfSourceEmitter:'SpeedOfSourceEmitter',SpeedOfListener:'SpeedOfListener',SpeedOfAngleDelta:'SpeedOfAngleDelta',Count:'Count',ESourceEffectMotionFilterModSource_MAX:'ESourceEffectMotionFilterModSource_MAX', };
declare class SourceEffectMotionFilterModulationSettings { 
	ModulationSource: ESourceEffectMotionFilterModSource;
	ModulationInputRange: Vector2D;
	ModulationOutputMinimumRange: Vector2D;
	ModulationOutputMaximumRange: Vector2D;
	UpdateEaseMS: number;
	clone() : SourceEffectMotionFilterModulationSettings;
	static C(Other: UObject | any): SourceEffectMotionFilterModulationSettings;
}

declare class SourceEffectMotionFilterSettings { 
	MotionFilterTopology: ESourceEffectMotionFilterTopology;
	MotionFilterMix: number;
	FilterASettings: SourceEffectIndividualFilterSettings;
	FilterBSettings: SourceEffectIndividualFilterSettings;
	ModulationMappings: Map<ESourceEffectMotionFilterModDestination, SourceEffectMotionFilterModulationSettings>;
	DryVolumeDb: number;
	clone() : SourceEffectMotionFilterSettings;
	static C(Other: UObject | any): SourceEffectMotionFilterSettings;
}

declare class SourceEffectMotionFilterPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectMotionFilterSettings;
	static Load(ResourceName: string): SourceEffectMotionFilterPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectMotionFilterPreset;
	static GetDefaultObject(): SourceEffectMotionFilterPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectMotionFilterPreset;
	SetSettings(InSettings: SourceEffectMotionFilterSettings): void;
	static C(Other: UObject | any): SourceEffectMotionFilterPreset;
}

declare class SourceEffectPannerSettings { 
	Spread: number;
	Pan: number;
	clone() : SourceEffectPannerSettings;
	static C(Other: UObject | any): SourceEffectPannerSettings;
}

declare class SourceEffectPannerPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectPannerSettings;
	static Load(ResourceName: string): SourceEffectPannerPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectPannerPreset;
	static GetDefaultObject(): SourceEffectPannerPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectPannerPreset;
	SetSettings(InSettings: SourceEffectPannerSettings): void;
	static C(Other: UObject | any): SourceEffectPannerPreset;
}

declare type EPhaserLFOType = 'Sine' | 'UpSaw' | 'DownSaw' | 'Square' | 'Triangle' | 'Exponential' | 'RandomSampleHold' | 'Count' | 'EPhaserLFOType_MAX';
declare var EPhaserLFOType : { Sine:'Sine',UpSaw:'UpSaw',DownSaw:'DownSaw',Square:'Square',Triangle:'Triangle',Exponential:'Exponential',RandomSampleHold:'RandomSampleHold',Count:'Count',EPhaserLFOType_MAX:'EPhaserLFOType_MAX', };
declare class SourceEffectPhaserSettings { 
	WetLevel: number;
	Frequency: number;
	Feedback: number;
	LFOType: EPhaserLFOType;
	UseQuadraturePhase: boolean;
	clone() : SourceEffectPhaserSettings;
	static C(Other: UObject | any): SourceEffectPhaserSettings;
}

declare class SourceEffectPhaserPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectPhaserSettings;
	static Load(ResourceName: string): SourceEffectPhaserPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectPhaserPreset;
	static GetDefaultObject(): SourceEffectPhaserPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectPhaserPreset;
	SetSettings(InSettings: SourceEffectPhaserSettings): void;
	static C(Other: UObject | any): SourceEffectPhaserPreset;
}

declare type ERingModulatorTypeSourceEffect = 'Sine' | 'Saw' | 'Triangle' | 'Square' | 'Count' | 'ERingModulatorTypeSourceEffect_MAX';
declare var ERingModulatorTypeSourceEffect : { Sine:'Sine',Saw:'Saw',Triangle:'Triangle',Square:'Square',Count:'Count',ERingModulatorTypeSourceEffect_MAX:'ERingModulatorTypeSourceEffect_MAX', };
declare class SourceEffectRingModulationSettings { 
	ModulatorType: ERingModulatorTypeSourceEffect;
	Frequency: number;
	Depth: number;
	DryLevel: number;
	WetLevel: number;
	AudioBusModulator: AudioBus;
	clone() : SourceEffectRingModulationSettings;
	static C(Other: UObject | any): SourceEffectRingModulationSettings;
}

declare class SourceEffectRingModulationPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectRingModulationSettings;
	static Load(ResourceName: string): SourceEffectRingModulationPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectRingModulationPreset;
	static GetDefaultObject(): SourceEffectRingModulationPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectRingModulationPreset;
	SetSettings(InSettings: SourceEffectRingModulationSettings): void;
	static C(Other: UObject | any): SourceEffectRingModulationPreset;
}

declare class SourceEffectSimpleDelaySettings { 
	SpeedOfSound: number;
	DelayAmount: number;
	DryAmount: number;
	WetAmount: number;
	Feedback: number;
	bDelayBasedOnDistance: boolean;
	clone() : SourceEffectSimpleDelaySettings;
	static C(Other: UObject | any): SourceEffectSimpleDelaySettings;
}

declare class SourceEffectSimpleDelayPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectSimpleDelaySettings;
	static Load(ResourceName: string): SourceEffectSimpleDelayPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectSimpleDelayPreset;
	static GetDefaultObject(): SourceEffectSimpleDelayPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectSimpleDelayPreset;
	SetSettings(InSettings: SourceEffectSimpleDelaySettings): void;
	static C(Other: UObject | any): SourceEffectSimpleDelayPreset;
}

declare type EStereoDelaySourceEffect = 'Normal' | 'Cross' | 'PingPong' | 'Count' | 'EStereoDelaySourceEffect_MAX';
declare var EStereoDelaySourceEffect : { Normal:'Normal',Cross:'Cross',PingPong:'PingPong',Count:'Count',EStereoDelaySourceEffect_MAX:'EStereoDelaySourceEffect_MAX', };
declare type EStereoDelayFiltertype = 'Lowpass' | 'Highpass' | 'Bandpass' | 'Notch' | 'Count' | 'EStereoDelayFiltertype_MAX';
declare var EStereoDelayFiltertype : { Lowpass:'Lowpass',Highpass:'Highpass',Bandpass:'Bandpass',Notch:'Notch',Count:'Count',EStereoDelayFiltertype_MAX:'EStereoDelayFiltertype_MAX', };
declare class SourceEffectStereoDelaySettings { 
	DelayMode: EStereoDelaySourceEffect;
	DelayTimeMsec: number;
	Feedback: number;
	DelayRatio: number;
	WetLevel: number;
	DryLevel: number;
	bFilterEnabled: boolean;
	FilterType: EStereoDelayFiltertype;
	FilterFrequency: number;
	FilterQ: number;
	clone() : SourceEffectStereoDelaySettings;
	static C(Other: UObject | any): SourceEffectStereoDelaySettings;
}

declare class SourceEffectStereoDelayPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectStereoDelaySettings;
	static Load(ResourceName: string): SourceEffectStereoDelayPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectStereoDelayPreset;
	static GetDefaultObject(): SourceEffectStereoDelayPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectStereoDelayPreset;
	SetSettings(InSettings: SourceEffectStereoDelaySettings): void;
	static C(Other: UObject | any): SourceEffectStereoDelayPreset;
}

declare class SourceEffectWaveShaperSettings { 
	Amount: number;
	OutputGainDb: number;
	clone() : SourceEffectWaveShaperSettings;
	static C(Other: UObject | any): SourceEffectWaveShaperSettings;
}

declare class SourceEffectWaveShaperPreset extends SoundEffectSourcePreset { 
	Settings: SourceEffectWaveShaperSettings;
	static Load(ResourceName: string): SourceEffectWaveShaperPreset;
	static Find(Outer: UObject, ResourceName: string): SourceEffectWaveShaperPreset;
	static GetDefaultObject(): SourceEffectWaveShaperPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SourceEffectWaveShaperPreset;
	SetSettings(InSettings: SourceEffectWaveShaperSettings): void;
	static C(Other: UObject | any): SourceEffectWaveShaperPreset;
}

declare class AudioImpulseResponse extends UObject { 
	ImpulseResponse: number[];
	NumChannels: number;
	SampleRate: number;
	NormalizationVolumeDb: number;
	bTrueStereo: boolean;
	IRData: number[];
	static Load(ResourceName: string): AudioImpulseResponse;
	static Find(Outer: UObject, ResourceName: string): AudioImpulseResponse;
	static GetDefaultObject(): AudioImpulseResponse;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioImpulseResponse;
	static C(Other: UObject | any): AudioImpulseResponse;
}

declare class SubmixEffectConvolutionReverbSettings { 
	NormalizationVolumeDb: number;
	bBypass: boolean;
	bMixInputChannelFormatToImpulseResponseFormat: boolean;
	bMixReverbOutputToOutputChannelFormat: boolean;
	SurroundRearChannelBleedDb: number;
	bInvertRearChannelBleedPhase: boolean;
	bSurroundRearChannelFlip: boolean;
	SurroundRearChannelBleedAmount: number;
	ImpulseResponse: AudioImpulseResponse;
	AllowHArdwareAcceleration: boolean;
	clone() : SubmixEffectConvolutionReverbSettings;
	static C(Other: UObject | any): SubmixEffectConvolutionReverbSettings;
}

declare type ESubmixEffectConvolutionReverbBlockSize = 'BlockSize256' | 'BlockSize512' | 'BlockSize1024' | 'ESubmixEffectConvolutionReverbBlockSize_MAX';
declare var ESubmixEffectConvolutionReverbBlockSize : { BlockSize256:'BlockSize256',BlockSize512:'BlockSize512',BlockSize1024:'BlockSize1024',ESubmixEffectConvolutionReverbBlockSize_MAX:'ESubmixEffectConvolutionReverbBlockSize_MAX', };
declare class SubmixEffectConvolutionReverbPreset extends SoundEffectSubmixPreset { 
	ImpulseResponse: AudioImpulseResponse;
	Settings: SubmixEffectConvolutionReverbSettings;
	BlockSize: ESubmixEffectConvolutionReverbBlockSize;
	bEnableHardwareAcceleration: boolean;
	static Load(ResourceName: string): SubmixEffectConvolutionReverbPreset;
	static Find(Outer: UObject, ResourceName: string): SubmixEffectConvolutionReverbPreset;
	static GetDefaultObject(): SubmixEffectConvolutionReverbPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubmixEffectConvolutionReverbPreset;
	SetSettings(InSettings: SubmixEffectConvolutionReverbSettings): void;
	SetImpulseResponse(InImpulseResponse: AudioImpulseResponse): void;
	static C(Other: UObject | any): SubmixEffectConvolutionReverbPreset;
}

declare class SubmixEffectDelaySettings { 
	MaximumDelayLength: number;
	InterpolationTime: number;
	DelayLength: number;
	clone() : SubmixEffectDelaySettings;
	static C(Other: UObject | any): SubmixEffectDelaySettings;
	SetDelayLength(DelayLength?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
	SetInterpolationTime(InterpolationTime?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
	SetMaximumDelayLength(MaximumDelayLength?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
	static SetDelayLength(DelaySettings?: SubmixEffectDelaySettings,DelayLength?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
	static SetInterpolationTime(DelaySettings?: SubmixEffectDelaySettings,InterpolationTime?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
	static SetMaximumDelayLength(DelaySettings?: SubmixEffectDelaySettings,MaximumDelayLength?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
}

declare class SubmixEffectDelayStatics extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): SubmixEffectDelayStatics;
	static Find(Outer: UObject, ResourceName: string): SubmixEffectDelayStatics;
	static GetDefaultObject(): SubmixEffectDelayStatics;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubmixEffectDelayStatics;
	static SetMaximumDelayLength(DelaySettings?: SubmixEffectDelaySettings,MaximumDelayLength?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
	static SetInterpolationTime(DelaySettings?: SubmixEffectDelaySettings,InterpolationTime?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
	static SetDelayLength(DelaySettings?: SubmixEffectDelaySettings,DelayLength?: number): {DelaySettings: SubmixEffectDelaySettings, $: SubmixEffectDelaySettings};
	static C(Other: UObject | any): SubmixEffectDelayStatics;
}

declare class SubmixEffectDelayPreset extends SoundEffectSubmixPreset { 
	Settings: SubmixEffectDelaySettings;
	DynamicSettings: SubmixEffectDelaySettings;
	static Load(ResourceName: string): SubmixEffectDelayPreset;
	static Find(Outer: UObject, ResourceName: string): SubmixEffectDelayPreset;
	static GetDefaultObject(): SubmixEffectDelayPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubmixEffectDelayPreset;
	SetSettings(InSettings: SubmixEffectDelaySettings): void;
	SetInterpolationTime(Time: number): void;
	SetDelay(Length: number): void;
	SetDefaultSettings(InSettings: SubmixEffectDelaySettings): void;
	GetMaxDelayInMilliseconds(): number;
	static C(Other: UObject | any): SubmixEffectDelayPreset;
}

declare type ESubmixFilterType = 'LowPass' | 'HighPass' | 'BandPass' | 'BandStop' | 'Count' | 'ESubmixFilterType_MAX';
declare var ESubmixFilterType : { LowPass:'LowPass',HighPass:'HighPass',BandPass:'BandPass',BandStop:'BandStop',Count:'Count',ESubmixFilterType_MAX:'ESubmixFilterType_MAX', };
declare type ESubmixFilterAlgorithm = 'OnePole' | 'StateVariable' | 'Ladder' | 'Count' | 'ESubmixFilterAlgorithm_MAX';
declare var ESubmixFilterAlgorithm : { OnePole:'OnePole',StateVariable:'StateVariable',Ladder:'Ladder',Count:'Count',ESubmixFilterAlgorithm_MAX:'ESubmixFilterAlgorithm_MAX', };
declare class SubmixEffectFilterSettings { 
	FilterType: ESubmixFilterType;
	FilterAlgorithm: ESubmixFilterAlgorithm;
	FilterFrequency: number;
	FilterQ: number;
	clone() : SubmixEffectFilterSettings;
	static C(Other: UObject | any): SubmixEffectFilterSettings;
}

declare class SubmixEffectFilterPreset extends SoundEffectSubmixPreset { 
	Settings: SubmixEffectFilterSettings;
	static Load(ResourceName: string): SubmixEffectFilterPreset;
	static Find(Outer: UObject, ResourceName: string): SubmixEffectFilterPreset;
	static GetDefaultObject(): SubmixEffectFilterPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubmixEffectFilterPreset;
	SetSettings(InSettings: SubmixEffectFilterSettings): void;
	SetFilterType(InType: ESubmixFilterType): void;
	SetFilterQMod(InQ: number): void;
	SetFilterQ(InQ: number): void;
	SetFilterCutoffFrequencyMod(InFrequency: number): void;
	SetFilterCutoffFrequency(InFrequency: number): void;
	SetFilterAlgorithm(InAlgorithm: ESubmixFilterAlgorithm): void;
	static C(Other: UObject | any): SubmixEffectFilterPreset;
}

declare class SubmixEffectFlexiverbSettings { 
	PreDelay: number;
	DecayTime: number;
	RoomDampening: number;
	Complexity: number;
	clone() : SubmixEffectFlexiverbSettings;
	static C(Other: UObject | any): SubmixEffectFlexiverbSettings;
}

declare class SubmixEffectFlexiverbPreset extends SoundEffectSubmixPreset { 
	Settings: SubmixEffectFlexiverbSettings;
	static Load(ResourceName: string): SubmixEffectFlexiverbPreset;
	static Find(Outer: UObject, ResourceName: string): SubmixEffectFlexiverbPreset;
	static GetDefaultObject(): SubmixEffectFlexiverbPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubmixEffectFlexiverbPreset;
	SetSettings(InSettings: SubmixEffectFlexiverbSettings): void;
	static C(Other: UObject | any): SubmixEffectFlexiverbPreset;
}

declare class DynamicsBandSettings { 
	CrossoverTopFrequency: number;
	AttackTimeMsec: number;
	ReleaseTimeMsec: number;
	ThresholdDb: number;
	Ratio: number;
	KneeBandwidthDb: number;
	InputGainDb: number;
	OutputGainDb: number;
	clone() : DynamicsBandSettings;
	static C(Other: UObject | any): DynamicsBandSettings;
}

declare class SubmixEffectMultibandCompressorSettings { 
	DynamicsProcessorType: ESubmixEffectDynamicsProcessorType;
	PeakMode: ESubmixEffectDynamicsPeakMode;
	LinkMode: ESubmixEffectDynamicsChannelLinkMode;
	LookAheadMsec: number;
	bAnalogMode: boolean;
	bFourPole: boolean;
	bBypass: boolean;
	KeySource: ESubmixEffectDynamicsKeySource;
	ExternalAudioBus: AudioBus;
	ExternalSubmix: SoundSubmix;
	KeyGainDb: number;
	bKeyAudition: boolean;
	Bands: DynamicsBandSettings[];
	clone() : SubmixEffectMultibandCompressorSettings;
	static C(Other: UObject | any): SubmixEffectMultibandCompressorSettings;
}

declare class SubmixEffectMultibandCompressorPreset extends SoundEffectSubmixPreset { 
	Settings: SubmixEffectMultibandCompressorSettings;
	static Load(ResourceName: string): SubmixEffectMultibandCompressorPreset;
	static Find(Outer: UObject, ResourceName: string): SubmixEffectMultibandCompressorPreset;
	static GetDefaultObject(): SubmixEffectMultibandCompressorPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubmixEffectMultibandCompressorPreset;
	SetSettings(InSettings: SubmixEffectMultibandCompressorSettings): void;
	SetExternalSubmix(Submix: SoundSubmix): void;
	SetAudioBus(AudioBus: AudioBus): void;
	ResetKey(): void;
	static C(Other: UObject | any): SubmixEffectMultibandCompressorPreset;
}

declare class SubmixEffectStereoDelaySettings { 
	DelayMode: EStereoDelaySourceEffect;
	DelayTimeMsec: number;
	Feedback: number;
	DelayRatio: number;
	WetLevel: number;
	DryLevel: number;
	bFilterEnabled: boolean;
	FilterType: EStereoDelayFiltertype;
	FilterFrequency: number;
	FilterQ: number;
	clone() : SubmixEffectStereoDelaySettings;
	static C(Other: UObject | any): SubmixEffectStereoDelaySettings;
}

declare class SubmixEffectStereoDelayPreset extends SoundEffectSubmixPreset { 
	Settings: SubmixEffectStereoDelaySettings;
	static Load(ResourceName: string): SubmixEffectStereoDelayPreset;
	static Find(Outer: UObject, ResourceName: string): SubmixEffectStereoDelayPreset;
	static GetDefaultObject(): SubmixEffectStereoDelayPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubmixEffectStereoDelayPreset;
	SetSettings(InSettings: SubmixEffectStereoDelaySettings): void;
	static C(Other: UObject | any): SubmixEffectStereoDelayPreset;
}

declare type ETapLineMode = 'SendToChannel' | 'Panning' | 'Disabled' | 'ETapLineMode_MAX';
declare var ETapLineMode : { SendToChannel:'SendToChannel',Panning:'Panning',Disabled:'Disabled',ETapLineMode_MAX:'ETapLineMode_MAX', };
declare class TapDelayInfo { 
	TapLineMode: ETapLineMode;
	DelayLength: number;
	Gain: number;
	OutputChannel: number;
	PanInDegrees: number;
	TapId: number;
	clone() : TapDelayInfo;
	static C(Other: UObject | any): TapDelayInfo;
}

declare class SubmixEffectTapDelaySettings { 
	MaximumDelayLength: number;
	InterpolationTime: number;
	Taps: TapDelayInfo[];
	clone() : SubmixEffectTapDelaySettings;
	static C(Other: UObject | any): SubmixEffectTapDelaySettings;
}

declare class SubmixEffectTapDelayPreset extends SoundEffectSubmixPreset { 
	Settings: SubmixEffectTapDelaySettings;
	static Load(ResourceName: string): SubmixEffectTapDelayPreset;
	static Find(Outer: UObject, ResourceName: string): SubmixEffectTapDelayPreset;
	static GetDefaultObject(): SubmixEffectTapDelayPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubmixEffectTapDelayPreset;
	SetTap(TapId: number,TapInfo: TapDelayInfo): void;
	SetSettings(InSettings: SubmixEffectTapDelaySettings): void;
	SetInterpolationTime(Time: number): void;
	RemoveTap(TapId: number): void;
	GetTapIds(TapIds?: number[]): {TapIds: number[]};
	GetTap(TapId: number,TapInfo?: TapDelayInfo): {TapInfo: TapDelayInfo};
	GetMaxDelayInMilliseconds(): number;
	AddTap(TapId?: number): {TapId: number};
	static C(Other: UObject | any): SubmixEffectTapDelayPreset;
}

declare class Synth2DSliderStyle extends SlateWidgetStyle { 
	NormalThumbImage: SlateBrush;
	DisabledThumbImage: SlateBrush;
	NormalBarImage: SlateBrush;
	DisabledBarImage: SlateBrush;
	BackgroundImage: SlateBrush;
	BarThickness: number;
	clone() : Synth2DSliderStyle;
	static C(Other: UObject | any): Synth2DSliderStyle;
}

declare class Synth2DSlider extends Widget { 
	ValueX: number;
	ValueY: number;
	ValueXDelegate: UnrealEngineDelegate<() => number>;
	ValueYDelegate: UnrealEngineDelegate<() => number>;
	WidgetStyle: Synth2DSliderStyle;
	SliderHandleColor: LinearColor;
	IndentHandle: boolean;
	Locked: boolean;
	StepSize: number;
	IsFocusable: boolean;
	OnMouseCaptureBegin: UnrealEngineMulticastDelegate<() => void>;
	OnMouseCaptureEnd: UnrealEngineMulticastDelegate<() => void>;
	OnControllerCaptureBegin: UnrealEngineMulticastDelegate<() => void>;
	OnControllerCaptureEnd: UnrealEngineMulticastDelegate<() => void>;
	OnValueChangedX: UnrealEngineMulticastDelegate<(Value: number) => void>;
	OnValueChangedY: UnrealEngineMulticastDelegate<(Value: number) => void>;
	static Load(ResourceName: string): Synth2DSlider;
	static Find(Outer: UObject, ResourceName: string): Synth2DSlider;
	static GetDefaultObject(): Synth2DSlider;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): Synth2DSlider;
	SetValue(InValue: Vector2D): void;
	SetStepSize(InValue: number): void;
	SetSliderHandleColor(InValue: LinearColor): void;
	SetLocked(InValue: boolean): void;
	SetIndentHandle(InValue: boolean): void;
	GetValue(): Vector2D;
	static C(Other: UObject | any): Synth2DSlider;
}

declare type EGranularSynthSeekType = 'FromBeginning' | 'FromCurrentPosition' | 'Count' | 'EGranularSynthSeekType_MAX';
declare var EGranularSynthSeekType : { FromBeginning:'FromBeginning',FromCurrentPosition:'FromCurrentPosition',Count:'Count',EGranularSynthSeekType_MAX:'EGranularSynthSeekType_MAX', };
declare type EGranularSynthEnvelopeType = 'Rectangular' | 'Triangle' | 'DownwardTriangle' | 'UpwardTriangle' | 'ExponentialDecay' | 'ExponentialIncrease' | 'Gaussian' | 'Hanning' | 'Lanczos' | 'Cosine' | 'CosineSquared' | 'Welch' | 'Blackman' | 'BlackmanHarris' | 'Count' | 'EGranularSynthEnvelopeType_MAX';
declare var EGranularSynthEnvelopeType : { Rectangular:'Rectangular',Triangle:'Triangle',DownwardTriangle:'DownwardTriangle',UpwardTriangle:'UpwardTriangle',ExponentialDecay:'ExponentialDecay',ExponentialIncrease:'ExponentialIncrease',Gaussian:'Gaussian',Hanning:'Hanning',Lanczos:'Lanczos',Cosine:'Cosine',CosineSquared:'CosineSquared',Welch:'Welch',Blackman:'Blackman',BlackmanHarris:'BlackmanHarris',Count:'Count',EGranularSynthEnvelopeType_MAX:'EGranularSynthEnvelopeType_MAX', };
declare class GranularSynth extends SynthComponent { 
	GranulatedSoundWave: SoundWave;
	static Load(ResourceName: string): GranularSynth;
	static Find(Outer: UObject, ResourceName: string): GranularSynth;
	static GetDefaultObject(): GranularSynth;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): GranularSynth;
	SetSustainGain(SustainGain: number): void;
	SetSoundWave(InSoundWave: SoundWave): void;
	SetScrubMode(bScrubMode: boolean): void;
	SetReleaseTimeMsec(ReleaseTimeMsec: number): void;
	SetPlayheadTime(InPositionSec: number,LerpTimeSec: number,SeekType: EGranularSynthSeekType): void;
	SetPlaybackSpeed(InPlayheadRate: number): void;
	SetGrainVolume(BaseVolume: number,VolumeRange: Vector2D): void;
	SetGrainsPerSecond(InGrainsPerSecond: number): void;
	SetGrainProbability(InGrainProbability: number): void;
	SetGrainPitch(BasePitch: number,PitchRange: Vector2D): void;
	SetGrainPan(BasePan: number,PanRange: Vector2D): void;
	SetGrainEnvelopeType(EnvelopeType: EGranularSynthEnvelopeType): void;
	SetGrainDuration(BaseDurationMsec: number,DurationRange: Vector2D): void;
	SetDecayTime(DecayTimeMsec: number): void;
	SetAttackTime(AttackTimeMsec: number): void;
	NoteOn(Note: number,Velocity: number,Duration: number): void;
	NoteOff(Note: number,bKill: boolean): void;
	IsLoaded(): boolean;
	GetSampleDuration(): number;
	GetCurrentPlayheadTime(): number;
	static C(Other: UObject | any): GranularSynth;
}

declare class MonoWaveTableSynthPreset extends UObject { 
	PresetName: string;
	bLockKeyframesToGridBool: boolean;
	LockKeyframesToGrid: number;
	WaveTableResolution: number;
	WaveTable: RuntimeFloatCurve[];
	bNormalizeWaveTables: boolean;
	static Load(ResourceName: string): MonoWaveTableSynthPreset;
	static Find(Outer: UObject, ResourceName: string): MonoWaveTableSynthPreset;
	static GetDefaultObject(): MonoWaveTableSynthPreset;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MonoWaveTableSynthPreset;
	static C(Other: UObject | any): MonoWaveTableSynthPreset;
}

declare type CurveInterpolationType = 'AUTOINTERP' | 'LINEAR' | 'CONSTANT' | 'CurveInterpolationType_MAX';
declare var CurveInterpolationType : { AUTOINTERP:'AUTOINTERP',LINEAR:'LINEAR',CONSTANT:'CONSTANT',CurveInterpolationType_MAX:'CurveInterpolationType_MAX', };
declare class SynthComponentMonoWaveTable extends SynthComponent { 
	OnTableAltered: UnrealEngineMulticastDelegate<(TableIndex: number) => void>;
	OnNumTablesChanged: UnrealEngineMulticastDelegate<() => void>;
	CurrentPreset: MonoWaveTableSynthPreset;
	static Load(ResourceName: string): SynthComponentMonoWaveTable;
	static Find(Outer: UObject, ResourceName: string): SynthComponentMonoWaveTable;
	static GetDefaultObject(): SynthComponentMonoWaveTable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SynthComponentMonoWaveTable;
	SetWaveTablePosition(InPosition: number): void;
	SetSustainPedalState(InSustainPedalState: boolean): void;
	SetPosLfoType(InLfoType: ESynthLFOType): void;
	SetPosLfoFrequency(InLfoFrequency: number): void;
	SetPosLfoDepth(InLfoDepth: number): void;
	SetPositionEnvelopeSustainGain(InSustainGain: number): void;
	SetPositionEnvelopeReleaseTime(InReleaseTimeMsec: number): void;
	SetPositionEnvelopeInvert(bInInvert: boolean): void;
	SetPositionEnvelopeDepth(InDepth: number): void;
	SetPositionEnvelopeDecayTime(InDecayTimeMsec: number): void;
	SetPositionEnvelopeBiasInvert(bInBiasInvert: boolean): void;
	SetPositionEnvelopeBiasDepth(InDepth: number): void;
	SetPositionEnvelopeAttackTime(InAttackTimeMsec: number): void;
	SetLowPassFilterResonance(InNewQ: number): void;
	SetFrequencyWithMidiNote(InMidiNote: number): void;
	SetFrequencyPitchBend(FrequencyOffsetCents: number): void;
	SetFrequency(FrequencyHz: number): void;
	SetFilterEnvelopeSustainGain(InSustainGain: number): void;
	SetFilterEnvelopeReleaseTime(InReleaseTimeMsec: number): void;
	SetFilterEnvelopenDecayTime(InDecayTimeMsec: number): void;
	SetFilterEnvelopeInvert(bInInvert: boolean): void;
	SetFilterEnvelopeDepth(InDepth: number): void;
	SetFilterEnvelopeBiasInvert(bInBiasInvert: boolean): void;
	SetFilterEnvelopeBiasDepth(InDepth: number): void;
	SetFilterEnvelopeAttackTime(InAttackTimeMsec: number): void;
	SetCurveValue(TableIndex: number,KeyframeIndex: number,NewValue: number): boolean;
	SetCurveTangent(TableIndex: number,InNewTangent: number): boolean;
	SetCurveInterpolationType(InterpolationType: CurveInterpolationType,TableIndex: number): boolean;
	SetAmpEnvelopeSustainGain(InSustainGain: number): void;
	SetAmpEnvelopeReleaseTime(InReleaseTimeMsec: number): void;
	SetAmpEnvelopeInvert(bInInvert: boolean): void;
	SetAmpEnvelopeDepth(InDepth: number): void;
	SetAmpEnvelopeDecayTime(InDecayTimeMsec: number): void;
	SetAmpEnvelopeBiasInvert(bInBiasInvert: boolean): void;
	SetAmpEnvelopeBiasDepth(InDepth: number): void;
	SetAmpEnvelopeAttackTime(InAttackTimeMsec: number): void;
	RefreshWaveTable(index: number): void;
	RefreshAllWaveTables(): void;
	NoteOn(InMidiNote: number,InVelocity: number): void;
	NoteOff(InMidiNote: number): void;
	GetNumTableEntries(): number;
	GetMaxTableIndex(): number;
	GetKeyFrameValuesForTable(TableIndex: number): number[];
	GetCurveTangent(TableIndex: number): number;
	static C(Other: UObject | any): SynthComponentMonoWaveTable;
}

declare class SynthComponentToneGenerator extends SynthComponent { 
	Frequency: number;
	Volume: number;
	DistanceAttenuationCurve: RuntimeFloatCurve;
	DistanceRange: Vector2D;
	AttenuationDbAtMaxRange: number;
	static Load(ResourceName: string): SynthComponentToneGenerator;
	static Find(Outer: UObject, ResourceName: string): SynthComponentToneGenerator;
	static GetDefaultObject(): SynthComponentToneGenerator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SynthComponentToneGenerator;
	SetVolume(InVolume: number): void;
	SetFrequency(InFrequency: number): void;
	static C(Other: UObject | any): SynthComponentToneGenerator;
}

declare type ESamplePlayerSeekType = 'FromBeginning' | 'FromCurrentPosition' | 'FromEnd' | 'Count' | 'ESamplePlayerSeekType_MAX';
declare var ESamplePlayerSeekType : { FromBeginning:'FromBeginning',FromCurrentPosition:'FromCurrentPosition',FromEnd:'FromEnd',Count:'Count',ESamplePlayerSeekType_MAX:'ESamplePlayerSeekType_MAX', };
declare class SynthSamplePlayer extends SynthComponent { 
	SoundWave: SoundWave;
	OnSampleLoaded: UnrealEngineMulticastDelegate<() => void>;
	OnSamplePlaybackProgress: UnrealEngineMulticastDelegate<(ProgressPercent: number, ProgressTimeSeconds: number) => void>;
	static Load(ResourceName: string): SynthSamplePlayer;
	static Find(Outer: UObject, ResourceName: string): SynthSamplePlayer;
	static GetDefaultObject(): SynthSamplePlayer;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SynthSamplePlayer;
	SetSoundWave(InSoundWave: SoundWave): void;
	SetScrubTimeWidth(InScrubTimeWidthSec: number): void;
	SetScrubMode(bScrubMode: boolean): void;
	SetPitch(InPitch: number,TimeSec: number): void;
	SeekToTime(TimeSec: number,SeekType: ESamplePlayerSeekType,bWrap: boolean): void;
	IsLoaded(): boolean;
	GetSampleDuration(): number;
	GetCurrentPlaybackProgressTime(): number;
	GetCurrentPlaybackProgressPercent(): number;
	static C(Other: UObject | any): SynthSamplePlayer;
}

declare class SynthesisUtilitiesBlueprintFunctionLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): SynthesisUtilitiesBlueprintFunctionLibrary;
	static Find(Outer: UObject, ResourceName: string): SynthesisUtilitiesBlueprintFunctionLibrary;
	static GetDefaultObject(): SynthesisUtilitiesBlueprintFunctionLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SynthesisUtilitiesBlueprintFunctionLibrary;
	static GetLogFrequency(InLinearValue: number,InDomainMin: number,InDomainMax: number,InRangeMin: number,InRangeMax: number): number;
	static GetLinearFrequency(InLogFrequencyValue: number,InDomainMin: number,InDomainMax: number,InRangeMin: number,InRangeMax: number): number;
	static C(Other: UObject | any): SynthesisUtilitiesBlueprintFunctionLibrary;
}

declare type ESynthKnobSize = 'Medium' | 'Large' | 'Count' | 'ESynthKnobSize_MAX';
declare var ESynthKnobSize : { Medium:'Medium',Large:'Large',Count:'Count',ESynthKnobSize_MAX:'ESynthKnobSize_MAX', };
declare class SynthKnobStyle extends SlateWidgetStyle { 
	LargeKnob: SlateBrush;
	LargeKnobOverlay: SlateBrush;
	MediumKnob: SlateBrush;
	MediumKnobOverlay: SlateBrush;
	MinValueAngle: number;
	MaxValueAngle: number;
	KnobSize: ESynthKnobSize;
	clone() : SynthKnobStyle;
	static C(Other: UObject | any): SynthKnobStyle;
}

declare class SynthKnob extends Widget { 
	Value: number;
	StepSize: number;
	MouseSpeed: number;
	MouseFineTuneSpeed: number;
	ShowTooltipInfo: boolean;
	ParameterName: string;
	ParameterUnits: string;
	ValueDelegate: UnrealEngineDelegate<() => number>;
	WidgetStyle: SynthKnobStyle;
	Locked: boolean;
	IsFocusable: boolean;
	OnMouseCaptureBegin: UnrealEngineMulticastDelegate<() => void>;
	OnMouseCaptureEnd: UnrealEngineMulticastDelegate<() => void>;
	OnControllerCaptureBegin: UnrealEngineMulticastDelegate<() => void>;
	OnControllerCaptureEnd: UnrealEngineMulticastDelegate<() => void>;
	OnValueChanged: UnrealEngineMulticastDelegate<(Value: number) => void>;
	static Load(ResourceName: string): SynthKnob;
	static Find(Outer: UObject, ResourceName: string): SynthKnob;
	static GetDefaultObject(): SynthKnob;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SynthKnob;
	SetValue(InValue: number): void;
	SetStepSize(InValue: number): void;
	SetLocked(InValue: boolean): void;
	GetValue(): number;
	static C(Other: UObject | any): SynthKnob;
}

declare class NumTablesChanged__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): NumTablesChanged__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): NumTablesChanged__PythonCallable;
	static GetDefaultObject(): NumTablesChanged__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): NumTablesChanged__PythonCallable;
	static C(Other: UObject | any): NumTablesChanged__PythonCallable;
}

declare class OnControllerCaptureBeginEventSynth2D__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnControllerCaptureBeginEventSynth2D__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnControllerCaptureBeginEventSynth2D__PythonCallable;
	static GetDefaultObject(): OnControllerCaptureBeginEventSynth2D__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnControllerCaptureBeginEventSynth2D__PythonCallable;
	static C(Other: UObject | any): OnControllerCaptureBeginEventSynth2D__PythonCallable;
}

declare class OnControllerCaptureEndEventSynth2D__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnControllerCaptureEndEventSynth2D__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnControllerCaptureEndEventSynth2D__PythonCallable;
	static GetDefaultObject(): OnControllerCaptureEndEventSynth2D__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnControllerCaptureEndEventSynth2D__PythonCallable;
	static C(Other: UObject | any): OnControllerCaptureEndEventSynth2D__PythonCallable;
}

declare class OnEnvelopeFollowerUpdate__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnEnvelopeFollowerUpdate__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnEnvelopeFollowerUpdate__PythonCallable;
	static GetDefaultObject(): OnEnvelopeFollowerUpdate__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnEnvelopeFollowerUpdate__PythonCallable;
	static C(Other: UObject | any): OnEnvelopeFollowerUpdate__PythonCallable;
}

declare class OnFloatValueChangedEventSynth2D__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnFloatValueChangedEventSynth2D__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnFloatValueChangedEventSynth2D__PythonCallable;
	static GetDefaultObject(): OnFloatValueChangedEventSynth2D__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnFloatValueChangedEventSynth2D__PythonCallable;
	static C(Other: UObject | any): OnFloatValueChangedEventSynth2D__PythonCallable;
}

declare class OnMouseCaptureBeginEventSynth2D__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnMouseCaptureBeginEventSynth2D__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnMouseCaptureBeginEventSynth2D__PythonCallable;
	static GetDefaultObject(): OnMouseCaptureBeginEventSynth2D__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnMouseCaptureBeginEventSynth2D__PythonCallable;
	static C(Other: UObject | any): OnMouseCaptureBeginEventSynth2D__PythonCallable;
}

declare class OnMouseCaptureEndEventSynth2D__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnMouseCaptureEndEventSynth2D__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnMouseCaptureEndEventSynth2D__PythonCallable;
	static GetDefaultObject(): OnMouseCaptureEndEventSynth2D__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnMouseCaptureEndEventSynth2D__PythonCallable;
	static C(Other: UObject | any): OnMouseCaptureEndEventSynth2D__PythonCallable;
}

declare class OnSampleLoaded__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnSampleLoaded__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnSampleLoaded__PythonCallable;
	static GetDefaultObject(): OnSampleLoaded__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnSampleLoaded__PythonCallable;
	static C(Other: UObject | any): OnSampleLoaded__PythonCallable;
}

declare class OnSamplePlaybackProgress__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnSamplePlaybackProgress__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnSamplePlaybackProgress__PythonCallable;
	static GetDefaultObject(): OnSamplePlaybackProgress__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnSamplePlaybackProgress__PythonCallable;
	static C(Other: UObject | any): OnSamplePlaybackProgress__PythonCallable;
}

declare class OnTableAltered__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnTableAltered__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnTableAltered__PythonCallable;
	static GetDefaultObject(): OnTableAltered__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnTableAltered__PythonCallable;
	static C(Other: UObject | any): OnTableAltered__PythonCallable;
}

declare class AudioImpulseResponseFactory extends Factory { 
	static Load(ResourceName: string): AudioImpulseResponseFactory;
	static Find(Outer: UObject, ResourceName: string): AudioImpulseResponseFactory;
	static GetDefaultObject(): AudioImpulseResponseFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioImpulseResponseFactory;
	static C(Other: UObject | any): AudioImpulseResponseFactory;
}

declare class ModularSynthPresetBankFactory extends Factory { 
	static Load(ResourceName: string): ModularSynthPresetBankFactory;
	static Find(Outer: UObject, ResourceName: string): ModularSynthPresetBankFactory;
	static GetDefaultObject(): ModularSynthPresetBankFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ModularSynthPresetBankFactory;
	static C(Other: UObject | any): ModularSynthPresetBankFactory;
}

declare class MonoWaveTableSynthPresetFactory extends Factory { 
	static Load(ResourceName: string): MonoWaveTableSynthPresetFactory;
	static Find(Outer: UObject, ResourceName: string): MonoWaveTableSynthPresetFactory;
	static GetDefaultObject(): MonoWaveTableSynthPresetFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MonoWaveTableSynthPresetFactory;
	static C(Other: UObject | any): MonoWaveTableSynthPresetFactory;
}

declare class SynthesisEditorSettings extends DeveloperSettings { 
	static Load(ResourceName: string): SynthesisEditorSettings;
	static Find(Outer: UObject, ResourceName: string): SynthesisEditorSettings;
	static GetDefaultObject(): SynthesisEditorSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SynthesisEditorSettings;
	static C(Other: UObject | any): SynthesisEditorSettings;
}

declare class ContentBrowserClassDataSource extends ContentBrowserDataSource { 
	static Load(ResourceName: string): ContentBrowserClassDataSource;
	static Find(Outer: UObject, ResourceName: string): ContentBrowserClassDataSource;
	static GetDefaultObject(): ContentBrowserClassDataSource;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ContentBrowserClassDataSource;
	static C(Other: UObject | any): ContentBrowserClassDataSource;
}

declare class ContentBrowserAssetDataSource extends ContentBrowserDataSource { 
	static Load(ResourceName: string): ContentBrowserAssetDataSource;
	static Find(Outer: UObject, ResourceName: string): ContentBrowserAssetDataSource;
	static GetDefaultObject(): ContentBrowserAssetDataSource;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ContentBrowserAssetDataSource;
	static C(Other: UObject | any): ContentBrowserAssetDataSource;
}

declare class InterchangeGraphInspectorPipeline extends InterchangePipelineBase { 
	static Load(ResourceName: string): InterchangeGraphInspectorPipeline;
	static Find(Outer: UObject, ResourceName: string): InterchangeGraphInspectorPipeline;
	static GetDefaultObject(): InterchangeGraphInspectorPipeline;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeGraphInspectorPipeline;
	static C(Other: UObject | any): InterchangeGraphInspectorPipeline;
}

declare class InterchangePipelineConfigurationGeneric extends InterchangePipelineConfigurationBase { 
	static Load(ResourceName: string): InterchangePipelineConfigurationGeneric;
	static Find(Outer: UObject, ResourceName: string): InterchangePipelineConfigurationGeneric;
	static GetDefaultObject(): InterchangePipelineConfigurationGeneric;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangePipelineConfigurationGeneric;
	static C(Other: UObject | any): InterchangePipelineConfigurationGeneric;
}

declare class InterchangeActorFactoryNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeActorFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeActorFactoryNode;
	static GetDefaultObject(): InterchangeActorFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeActorFactoryNode;
	SetCustomGlobalTransform(AttributeValue: Transform): boolean;
	SetCustomActorClassName(AttributeValue: string): boolean;
	GetCustomGlobalTransform(AttributeValue?: Transform): {AttributeValue: Transform, $: boolean};
	GetCustomActorClassName(AttributeValue?: string): {AttributeValue: string, $: boolean};
	static C(Other: UObject | any): InterchangeActorFactoryNode;
}

declare class InterchangeCameraNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeCameraNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeCameraNode;
	static GetDefaultObject(): InterchangeCameraNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeCameraNode;
	static C(Other: UObject | any): InterchangeCameraNode;
}

declare class InterchangeLightNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeLightNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeLightNode;
	static GetDefaultObject(): InterchangeLightNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeLightNode;
	static C(Other: UObject | any): InterchangeLightNode;
}

declare class InterchangeMaterialFactoryNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeMaterialFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeMaterialFactoryNode;
	static GetDefaultObject(): InterchangeMaterialFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeMaterialFactoryNode;
	SetTextureDependencyUid(DependencyUid: string): boolean;
	SetCustomTranslatedMaterialNodeUid(AttributeValue: string): boolean;
	SetCustomMaterialUsage(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomBlendMode(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	RemoveTextureDependencyUid(DependencyUid: string): boolean;
	InitializeMaterialNode(UniqueId: string,DisplayLabel: string,InAssetClass: string): void;
	GetTextureDependency(index: number,OutDependency?: string): {OutDependency: string};
	GetTextureDependencies(OutDependencies?: string[]): {OutDependencies: string[]};
	GetTextureDependeciesCount(): number;
	GetObjectClass(): UnrealEngineClass;
	GetCustomTranslatedMaterialNodeUid(AttributeValue?: string): {AttributeValue: string, $: boolean};
	GetCustomMaterialUsage(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomBlendMode(AttributeValue?: number): {AttributeValue: number, $: boolean};
	static C(Other: UObject | any): InterchangeMaterialFactoryNode;
}

declare type EInterchangeMaterialNodeParameterName = 'BaseColor' | 'EmissiveColor' | 'Specular' | 'Roughness' | 'Metallic' | 'Normal' | 'Opacity' | 'OpacityMask' | 'EInterchangeMaterialNodeParameterName_MAX';
declare var EInterchangeMaterialNodeParameterName : { BaseColor:'BaseColor',EmissiveColor:'EmissiveColor',Specular:'Specular',Roughness:'Roughness',Metallic:'Metallic',Normal:'Normal',Opacity:'Opacity',OpacityMask:'OpacityMask',EInterchangeMaterialNodeParameterName_MAX:'EInterchangeMaterialNodeParameterName_MAX', };
declare class InterchangeMaterialNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeMaterialNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeMaterialNode;
	static GetDefaultObject(): InterchangeMaterialNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeMaterialNode;
	SetTextureDependencyUid(DependencyUid: string): boolean;
	SetPayLoadKey(PayloadKey: string): void;
	RemoveTextureDependencyUid(DependencyUid: string): boolean;
	GetVectorParameterData(ParameterName: EInterchangeMaterialNodeParameterName,OutVectorData?: Vector): {OutVectorData: Vector, $: boolean};
	GetTextureParameterData(ParameterName: EInterchangeMaterialNodeParameterName,OutTextureUid?: string,OutUVSetIndex?: number,OutScaleU?: number,OutScaleV?: number): {OutTextureUid: string, OutUVSetIndex: number, OutScaleU: number, OutScaleV: number, $: boolean};
	GetTextureDependency(index: number,OutDependency?: string): {OutDependency: string};
	GetTextureDependencies(OutDependencies?: string[]): {OutDependencies: string[]};
	GetTextureDependeciesCount(): number;
	GetScalarParameterData(ParameterName: EInterchangeMaterialNodeParameterName,OutScalarData?: number): {OutScalarData: number, $: boolean};
	AddVectorParameterData(ParameterName: EInterchangeMaterialNodeParameterName,VectorData: Vector): void;
	AddTextureParameterData(ParameterName: EInterchangeMaterialNodeParameterName,TextureUid: string,UvSetIndex: number,ScaleU: number,ScaleV: number): void;
	AddScalarParameterData(ParameterName: EInterchangeMaterialNodeParameterName,ScalarData: number): void;
	static C(Other: UObject | any): InterchangeMaterialNode;
}

declare class InterchangeMeshNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeMeshNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeMeshNode;
	static GetDefaultObject(): InterchangeMeshNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeMeshNode;
	SetSkinnedMesh(bIsSkinnedMesh: boolean): boolean;
	SetSkeletonDependencyUid(DependencyUid: string): boolean;
	SetShapeDependencyUid(DependencyUid: string): boolean;
	SetSceneInstanceUid(DependencyUid: string): boolean;
	SetPayLoadKey(PayloadKey: string): void;
	SetMaterialDependencyUid(DependencyUid: string): boolean;
	SetCustomVertexCount(AttributeValue: number): boolean;
	SetCustomUVCount(AttributeValue: number): boolean;
	SetCustomPolygonCount(AttributeValue: number): boolean;
	SetCustomHasVertexTangent(AttributeValue: boolean): boolean;
	SetCustomHasVertexNormal(AttributeValue: boolean): boolean;
	SetCustomHasVertexColor(AttributeValue: boolean): boolean;
	SetCustomHasVertexBinormal(AttributeValue: boolean): boolean;
	SetCustomHasSmoothGroup(AttributeValue: boolean): boolean;
	SetCustomBoundingBox(AttributeValue: Box): boolean;
	SetBlendShapeName(BlendShapeName: string): boolean;
	SetBlendShape(bIsBlendShape: boolean): boolean;
	RemoveSkeletonDependencyUid(DependencyUid: string): boolean;
	RemoveShapeDependencyUid(DependencyUid: string): boolean;
	RemoveSceneInstanceUid(DependencyUid: string): boolean;
	RemoveMaterialDependencyUid(DependencyUid: string): boolean;
	IsSkinnedMesh(): boolean;
	IsBlendShape(): boolean;
	GetSkeletonDependency(index: number,OutDependency?: string): {OutDependency: string};
	GetSkeletonDependencies(OutDependencies?: string[]): {OutDependencies: string[]};
	GetSkeletonDependeciesCount(): number;
	GetShapeDependency(index: number,OutDependency?: string): {OutDependency: string};
	GetShapeDependencies(OutDependencies?: string[]): {OutDependencies: string[]};
	GetShapeDependeciesCount(): number;
	GetSceneInstanceUidsCount(): number;
	GetSceneInstanceUids(OutDependencies?: string[]): {OutDependencies: string[]};
	GetSceneInstanceUid(index: number,OutDependency?: string): {OutDependency: string};
	GetMaterialDependency(index: number,OutDependency?: string): {OutDependency: string};
	GetMaterialDependencies(OutDependencies?: string[]): {OutDependencies: string[]};
	GetMaterialDependeciesCount(): number;
	GetCustomVertexCount(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomUVCount(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomPolygonCount(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomHasVertexTangent(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomHasVertexNormal(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomHasVertexColor(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomHasVertexBinormal(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomHasSmoothGroup(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomBoundingBox(AttributeValue?: Box): {AttributeValue: Box, $: boolean};
	GetBlendShapeName(OutBlendShapeName?: string): {OutBlendShapeName: string, $: boolean};
	static C(Other: UObject | any): InterchangeMeshNode;
}

declare class InterchangePhysicsAssetFactoryNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangePhysicsAssetFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangePhysicsAssetFactoryNode;
	static GetDefaultObject(): InterchangePhysicsAssetFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangePhysicsAssetFactoryNode;
	SetCustomSkeletalMeshUid(AttributeValue: string): boolean;
	InitializePhysicsAssetNode(UniqueId: string,DisplayLabel: string,InAssetClass: string): void;
	GetObjectClass(): UnrealEngineClass;
	GetCustomSkeletalMeshUid(AttributeValue?: string): {AttributeValue: string, $: boolean};
	static C(Other: UObject | any): InterchangePhysicsAssetFactoryNode;
}

declare class InterchangeSceneNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeSceneNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeSceneNode;
	static GetDefaultObject(): InterchangeSceneNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeSceneNode;
	SetCustomLocalTransform(AttributeValue: Transform): boolean;
	SetCustomGlobalTransform(AttributeValue: Transform): boolean;
	SetCustomAssetInstanceUid(AttributeValue: string): boolean;
	RemoveSpecializedType(SpecializedType: string): boolean;
	RemoveMaterialDependencyUid(MaterialDependencyUid: string): boolean;
	IsSpecializedTypeContains(SpecializedType: string): boolean;
	GetSpecializedTypes(OutSpecializedTypes?: string[]): {OutSpecializedTypes: string[]};
	GetSpecializedTypeCount(): number;
	GetSpecializedType(index: number,OutSpecializedType?: string): {OutSpecializedType: string};
	GetMaterialDependencyUidsCount(): number;
	GetMaterialDependencyUids(OutMaterialDependencyUids?: string[]): {OutMaterialDependencyUids: string[]};
	GetMaterialDependencyUid(index: number,OutMaterialDependencyUid?: string): {OutMaterialDependencyUid: string};
	GetCustomLocalTransform(AttributeValue?: Transform): {AttributeValue: Transform, $: boolean};
	GetCustomGlobalTransform(AttributeValue?: Transform): {AttributeValue: Transform, $: boolean};
	GetCustomAssetInstanceUid(AttributeValue?: string): {AttributeValue: string, $: boolean};
	AddSpecializedType(SpecializedType: string): boolean;
	AddMaterialDependencyUid(MaterialDependencyUid: string): boolean;
	static C(Other: UObject | any): InterchangeSceneNode;
}

declare class InterchangeSkeletalMeshFactoryNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeSkeletalMeshFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeSkeletalMeshFactoryNode;
	static GetDefaultObject(): InterchangeSkeletalMeshFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeSkeletalMeshFactoryNode;
	SetCustomVertexColorReplace(AttributeValue: boolean): boolean;
	SetCustomVertexColorOverride(AttributeValue: Color): boolean;
	SetCustomVertexColorIgnore(AttributeValue: boolean): boolean;
	SetCustomSkeletonSoftObjectPath(AttributeValue: SoftObjectPath): boolean;
	SetCustomPhysicAssetSoftObjectPath(AttributeValue: SoftObjectPath): boolean;
	SetCustomImportMorphTarget(AttributeValue: boolean): boolean;
	SetCustomCreatePhysicsAsset(AttributeValue: boolean): boolean;
	RemoveLodDataUniqueId(LodDataUniqueId: string): boolean;
	InitializeSkeletalMeshNode(UniqueId: string,DisplayLabel: string,InAssetClass: string): void;
	GetObjectClass(): UnrealEngineClass;
	GetLodDataUniqueIds(OutLodDataUniqueIds?: string[]): {OutLodDataUniqueIds: string[]};
	GetLodDataCount(): number;
	GetCustomVertexColorReplace(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomVertexColorOverride(AttributeValue?: Color): {AttributeValue: Color, $: boolean};
	GetCustomVertexColorIgnore(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomSkeletonSoftObjectPath(AttributeValue?: SoftObjectPath): {AttributeValue: SoftObjectPath, $: boolean};
	GetCustomPhysicAssetSoftObjectPath(AttributeValue?: SoftObjectPath): {AttributeValue: SoftObjectPath, $: boolean};
	GetCustomImportMorphTarget(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomCreatePhysicsAsset(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	AddLodDataUniqueId(LodDataUniqueId: string): boolean;
	static C(Other: UObject | any): InterchangeSkeletalMeshFactoryNode;
}

declare class InterchangeSkeletalMeshLodDataNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeSkeletalMeshLodDataNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeSkeletalMeshLodDataNode;
	static GetDefaultObject(): InterchangeSkeletalMeshLodDataNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeSkeletalMeshLodDataNode;
	SetCustomSkeletonUid(AttributeValue: string): boolean;
	RemoveMeshUid(BlendShapeName: string): boolean;
	RemoveAllMeshes(): boolean;
	GetMeshUidsCount(): number;
	GetMeshUids(OutBlendShapeNames?: string[]): {OutBlendShapeNames: string[]};
	GetCustomSkeletonUid(AttributeValue?: string): {AttributeValue: string, $: boolean};
	AddMeshUid(BlendShapeName: string): boolean;
	static C(Other: UObject | any): InterchangeSkeletalMeshLodDataNode;
}

declare class InterchangeSkeletonFactoryNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeSkeletonFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeSkeletonFactoryNode;
	static GetDefaultObject(): InterchangeSkeletonFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeSkeletonFactoryNode;
	SetCustomRootJointUid(AttributeValue: string): boolean;
	InitializeSkeletonNode(UniqueId: string,DisplayLabel: string,InAssetClass: string): void;
	GetObjectClass(): UnrealEngineClass;
	GetCustomRootJointUid(AttributeValue?: string): {AttributeValue: string, $: boolean};
	static C(Other: UObject | any): InterchangeSkeletonFactoryNode;
}

declare class InterchangeStaticMeshFactoryNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeStaticMeshFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeStaticMeshFactoryNode;
	static GetDefaultObject(): InterchangeStaticMeshFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeStaticMeshFactoryNode;
	SetCustomVertexColorReplace(AttributeValue: boolean): boolean;
	SetCustomVertexColorOverride(AttributeValue: Color): boolean;
	SetCustomVertexColorIgnore(AttributeValue: boolean): boolean;
	RemoveLodDataUniqueId(LodDataUniqueId: string): boolean;
	InitializeStaticMeshNode(UniqueId: string,DisplayLabel: string,InAssetClass: string): void;
	GetObjectClass(): UnrealEngineClass;
	GetLodDataUniqueIds(OutLodDataUniqueIds?: string[]): {OutLodDataUniqueIds: string[]};
	GetLodDataCount(): number;
	GetCustomVertexColorReplace(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomVertexColorOverride(AttributeValue?: Color): {AttributeValue: Color, $: boolean};
	GetCustomVertexColorIgnore(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	AddLodDataUniqueId(LodDataUniqueId: string): boolean;
	static C(Other: UObject | any): InterchangeStaticMeshFactoryNode;
}

declare class InterchangeStaticMeshLodDataNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeStaticMeshLodDataNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeStaticMeshLodDataNode;
	static GetDefaultObject(): InterchangeStaticMeshLodDataNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeStaticMeshLodDataNode;
	RemoveMeshUid(MeshName: string): boolean;
	RemoveAllMeshes(): boolean;
	GetMeshUidsCount(): number;
	GetMeshUids(OutMeshNames?: string[]): {OutMeshNames: string[]};
	AddMeshUid(MeshName: string): boolean;
	static C(Other: UObject | any): InterchangeStaticMeshLodDataNode;
}

declare class InterchangeTextureFactoryNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeTextureFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureFactoryNode;
	static GetDefaultObject(): InterchangeTextureFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureFactoryNode;
	SetCustomVirtualTextureStreaming(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustomTranslatedTextureNodeUid(AttributeValue: string): boolean;
	SetCustomSRGB(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustomPowerOfTwoMode(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomPaddingColor(AttributeValue: Color,bAddApplyDelegate: boolean): boolean;
	SetCustomMipLoadOptions(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomMipGenSettings(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomMaxTextureSize(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomLossyCompressionAmount(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomLODGroup(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomLODBias(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomFilter(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomDownscaleOptions(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomDownscale(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomDeferCompression(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustomCompressionSettings(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomCompressionQuality(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomCompressionNoAlpha(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustomCompositeTextureMode(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomCompositePower(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomChromaKeyThreshold(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomChromaKeyColor(AttributeValue: Color,bAddApplyDelegate: boolean): boolean;
	SetCustombUseLegacyGamma(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustombPreserveBorder(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustombFlipGreenChannel(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustombDoScaleMipsForAlphaCoverage(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustombDitherMipMapAlpha(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustombChromaKeyTexture(AttributeValue: boolean,bAddApplyDelegate: boolean): boolean;
	SetCustomAlphaCoverageThresholds(AttributeValue: Vector4,bAddApplyDelegate: boolean): boolean;
	SetCustomAdjustVibrance(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAdjustSaturation(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAdjustRGBCurve(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAdjustMinAlpha(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAdjustMaxAlpha(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAdjustHue(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAdjustBrightnessCurve(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAdjustBrightness(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAddressY(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomAddressX(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	InitializeTextureNode(UniqueId: string,DisplayLabel: string,InAssetClass: string,InAssetName: string): void;
	GetObjectClass(): UnrealEngineClass;
	GetCustomVirtualTextureStreaming(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomTranslatedTextureNodeUid(AttributeValue?: string): {AttributeValue: string, $: boolean};
	GetCustomSRGB(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomPowerOfTwoMode(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomPaddingColor(AttributeValue?: Color): {AttributeValue: Color, $: boolean};
	GetCustomMipLoadOptions(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomMipGenSettings(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomMaxTextureSize(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomLossyCompressionAmount(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomLODGroup(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomLODBias(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomFilter(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomDownscaleOptions(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomDownscale(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomDeferCompression(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomCompressionSettings(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomCompressionQuality(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomCompressionNoAlpha(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomCompositeTextureMode(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomCompositePower(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomChromaKeyThreshold(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomChromaKeyColor(AttributeValue?: Color): {AttributeValue: Color, $: boolean};
	GetCustombUseLegacyGamma(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustombPreserveBorder(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustombFlipGreenChannel(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustombDoScaleMipsForAlphaCoverage(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustombDitherMipMapAlpha(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustombChromaKeyTexture(AttributeValue?: boolean): {AttributeValue: boolean, $: boolean};
	GetCustomAlphaCoverageThresholds(AttributeValue?: Vector4): {AttributeValue: Vector4, $: boolean};
	GetCustomAdjustVibrance(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAdjustSaturation(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAdjustRGBCurve(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAdjustMinAlpha(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAdjustMaxAlpha(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAdjustHue(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAdjustBrightnessCurve(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAdjustBrightness(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAddressY(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomAddressX(AttributeValue?: number): {AttributeValue: number, $: boolean};
	static C(Other: UObject | any): InterchangeTextureFactoryNode;
}

declare class InterchangeTexture2DArrayFactoryNode extends InterchangeTextureFactoryNode { 
	static Load(ResourceName: string): InterchangeTexture2DArrayFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTexture2DArrayFactoryNode;
	static GetDefaultObject(): InterchangeTexture2DArrayFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTexture2DArrayFactoryNode;
	SetCustomAddressZ(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	GetCustomAddressZ(AttributeValue?: number): {AttributeValue: number, $: boolean};
	static C(Other: UObject | any): InterchangeTexture2DArrayFactoryNode;
}

declare class InterchangeTextureNode extends InterchangeBaseNode { 
	static Load(ResourceName: string): InterchangeTextureNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureNode;
	static GetDefaultObject(): InterchangeTextureNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureNode;
	SetPayLoadKey(PayloadKey: string): void;
	static C(Other: UObject | any): InterchangeTextureNode;
}

declare class InterchangeTexture2DArrayNode extends InterchangeTextureNode { 
	static Load(ResourceName: string): InterchangeTexture2DArrayNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTexture2DArrayNode;
	static GetDefaultObject(): InterchangeTexture2DArrayNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTexture2DArrayNode;
	static C(Other: UObject | any): InterchangeTexture2DArrayNode;
}

declare class InterchangeTexture2DNode extends InterchangeTextureNode { 
	static Load(ResourceName: string): InterchangeTexture2DNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTexture2DNode;
	static GetDefaultObject(): InterchangeTexture2DNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTexture2DNode;
	SetSourceBlocks(InSourceBlocks: Map<number, string>): void;
	GetSourceBlocks(): Map<number, string>;
	ClearSourceBlocksData(): void;
	static C(Other: UObject | any): InterchangeTexture2DNode;
}

declare class InterchangeTextureCubeFactoryNode extends InterchangeTextureFactoryNode { 
	static Load(ResourceName: string): InterchangeTextureCubeFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureCubeFactoryNode;
	static GetDefaultObject(): InterchangeTextureCubeFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureCubeFactoryNode;
	static C(Other: UObject | any): InterchangeTextureCubeFactoryNode;
}

declare class InterchangeTextureCubeNode extends InterchangeTextureNode { 
	static Load(ResourceName: string): InterchangeTextureCubeNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureCubeNode;
	static GetDefaultObject(): InterchangeTextureCubeNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureCubeNode;
	static C(Other: UObject | any): InterchangeTextureCubeNode;
}

declare class InterchangeTextureLightProfileFactoryNode extends InterchangeTextureFactoryNode { 
	static Load(ResourceName: string): InterchangeTextureLightProfileFactoryNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureLightProfileFactoryNode;
	static GetDefaultObject(): InterchangeTextureLightProfileFactoryNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureLightProfileFactoryNode;
	SetCustomTextureMultiplier(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	SetCustomBrightness(AttributeValue: number,bAddApplyDelegate: boolean): boolean;
	GetCustomTextureMultiplier(AttributeValue?: number): {AttributeValue: number, $: boolean};
	GetCustomBrightness(AttributeValue?: number): {AttributeValue: number, $: boolean};
	static C(Other: UObject | any): InterchangeTextureLightProfileFactoryNode;
}

declare class InterchangeTextureLightProfileNode extends InterchangeTextureNode { 
	static Load(ResourceName: string): InterchangeTextureLightProfileNode;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureLightProfileNode;
	static GetDefaultObject(): InterchangeTextureLightProfileNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureLightProfileNode;
	static C(Other: UObject | any): InterchangeTextureLightProfileNode;
}

declare class InterchangeActorFactory extends InterchangeFactoryBase { 
	static Load(ResourceName: string): InterchangeActorFactory;
	static Find(Outer: UObject, ResourceName: string): InterchangeActorFactory;
	static GetDefaultObject(): InterchangeActorFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeActorFactory;
	static C(Other: UObject | any): InterchangeActorFactory;
}

declare class InterchangeBlockedTexturePayloadInterface extends Interface { 
	static Load(ResourceName: string): InterchangeBlockedTexturePayloadInterface;
	static Find(Outer: UObject, ResourceName: string): InterchangeBlockedTexturePayloadInterface;
	static GetDefaultObject(): InterchangeBlockedTexturePayloadInterface;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeBlockedTexturePayloadInterface;
	static C(Other: UObject | any): InterchangeBlockedTexturePayloadInterface;
}

declare class InterchangeBMPTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeBMPTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeBMPTranslator;
	static GetDefaultObject(): InterchangeBMPTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeBMPTranslator;
	static C(Other: UObject | any): InterchangeBMPTranslator;
}

declare class InterchangeDDSTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeDDSTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeDDSTranslator;
	static GetDefaultObject(): InterchangeDDSTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeDDSTranslator;
	static C(Other: UObject | any): InterchangeDDSTranslator;
}

declare class InterchangeEXRTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeEXRTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeEXRTranslator;
	static GetDefaultObject(): InterchangeEXRTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeEXRTranslator;
	static C(Other: UObject | any): InterchangeEXRTranslator;
}

declare class InterchangeFbxTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeFbxTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeFbxTranslator;
	static GetDefaultObject(): InterchangeFbxTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeFbxTranslator;
	static C(Other: UObject | any): InterchangeFbxTranslator;
}

declare class InterchangeHDRTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeHDRTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeHDRTranslator;
	static GetDefaultObject(): InterchangeHDRTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeHDRTranslator;
	static C(Other: UObject | any): InterchangeHDRTranslator;
}

declare class InterchangeIESTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeIESTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeIESTranslator;
	static GetDefaultObject(): InterchangeIESTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeIESTranslator;
	static C(Other: UObject | any): InterchangeIESTranslator;
}

declare class InterchangeJPGTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeJPGTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeJPGTranslator;
	static GetDefaultObject(): InterchangeJPGTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeJPGTranslator;
	static C(Other: UObject | any): InterchangeJPGTranslator;
}

declare class InterchangeMaterialFactory extends InterchangeFactoryBase { 
	static Load(ResourceName: string): InterchangeMaterialFactory;
	static Find(Outer: UObject, ResourceName: string): InterchangeMaterialFactory;
	static GetDefaultObject(): InterchangeMaterialFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeMaterialFactory;
	static C(Other: UObject | any): InterchangeMaterialFactory;
}

declare class InterchangePCXTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangePCXTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangePCXTranslator;
	static GetDefaultObject(): InterchangePCXTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangePCXTranslator;
	static C(Other: UObject | any): InterchangePCXTranslator;
}

declare class InterchangePhysicsAssetFactory extends InterchangeFactoryBase { 
	static Load(ResourceName: string): InterchangePhysicsAssetFactory;
	static Find(Outer: UObject, ResourceName: string): InterchangePhysicsAssetFactory;
	static GetDefaultObject(): InterchangePhysicsAssetFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangePhysicsAssetFactory;
	static C(Other: UObject | any): InterchangePhysicsAssetFactory;
}

declare class InterchangePNGTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangePNGTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangePNGTranslator;
	static GetDefaultObject(): InterchangePNGTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangePNGTranslator;
	static C(Other: UObject | any): InterchangePNGTranslator;
}

declare class InterchangePSDTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangePSDTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangePSDTranslator;
	static GetDefaultObject(): InterchangePSDTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangePSDTranslator;
	static C(Other: UObject | any): InterchangePSDTranslator;
}

declare class InterchangeSkeletalMeshFactory extends InterchangeFactoryBase { 
	static Load(ResourceName: string): InterchangeSkeletalMeshFactory;
	static Find(Outer: UObject, ResourceName: string): InterchangeSkeletalMeshFactory;
	static GetDefaultObject(): InterchangeSkeletalMeshFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeSkeletalMeshFactory;
	static C(Other: UObject | any): InterchangeSkeletalMeshFactory;
}

declare class InterchangeSkeletalMeshPayloadInterface extends Interface { 
	static Load(ResourceName: string): InterchangeSkeletalMeshPayloadInterface;
	static Find(Outer: UObject, ResourceName: string): InterchangeSkeletalMeshPayloadInterface;
	static GetDefaultObject(): InterchangeSkeletalMeshPayloadInterface;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeSkeletalMeshPayloadInterface;
	static C(Other: UObject | any): InterchangeSkeletalMeshPayloadInterface;
}

declare class InterchangeSkeletonFactory extends InterchangeFactoryBase { 
	static Load(ResourceName: string): InterchangeSkeletonFactory;
	static Find(Outer: UObject, ResourceName: string): InterchangeSkeletonFactory;
	static GetDefaultObject(): InterchangeSkeletonFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeSkeletonFactory;
	static C(Other: UObject | any): InterchangeSkeletonFactory;
}

declare class InterchangeSlicedTexturePayloadInterface extends Interface { 
	static Load(ResourceName: string): InterchangeSlicedTexturePayloadInterface;
	static Find(Outer: UObject, ResourceName: string): InterchangeSlicedTexturePayloadInterface;
	static GetDefaultObject(): InterchangeSlicedTexturePayloadInterface;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeSlicedTexturePayloadInterface;
	static C(Other: UObject | any): InterchangeSlicedTexturePayloadInterface;
}

declare class InterchangeStaticMeshFactory extends InterchangeFactoryBase { 
	static Load(ResourceName: string): InterchangeStaticMeshFactory;
	static Find(Outer: UObject, ResourceName: string): InterchangeStaticMeshFactory;
	static GetDefaultObject(): InterchangeStaticMeshFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeStaticMeshFactory;
	static C(Other: UObject | any): InterchangeStaticMeshFactory;
}

declare class InterchangeStaticMeshPayloadInterface extends Interface { 
	static Load(ResourceName: string): InterchangeStaticMeshPayloadInterface;
	static Find(Outer: UObject, ResourceName: string): InterchangeStaticMeshPayloadInterface;
	static GetDefaultObject(): InterchangeStaticMeshPayloadInterface;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeStaticMeshPayloadInterface;
	static C(Other: UObject | any): InterchangeStaticMeshPayloadInterface;
}

declare class InterchangeTextureFactory extends InterchangeFactoryBase { 
	static Load(ResourceName: string): InterchangeTextureFactory;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureFactory;
	static GetDefaultObject(): InterchangeTextureFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureFactory;
	static C(Other: UObject | any): InterchangeTextureFactory;
}

declare class InterchangeTextureLightProfilePayloadInterface extends Interface { 
	static Load(ResourceName: string): InterchangeTextureLightProfilePayloadInterface;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureLightProfilePayloadInterface;
	static GetDefaultObject(): InterchangeTextureLightProfilePayloadInterface;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureLightProfilePayloadInterface;
	static C(Other: UObject | any): InterchangeTextureLightProfilePayloadInterface;
}

declare class InterchangeTexturePayloadInterface extends Interface { 
	static Load(ResourceName: string): InterchangeTexturePayloadInterface;
	static Find(Outer: UObject, ResourceName: string): InterchangeTexturePayloadInterface;
	static GetDefaultObject(): InterchangeTexturePayloadInterface;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTexturePayloadInterface;
	static C(Other: UObject | any): InterchangeTexturePayloadInterface;
}

declare class InterchangeTGATranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeTGATranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeTGATranslator;
	static GetDefaultObject(): InterchangeTGATranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTGATranslator;
	static C(Other: UObject | any): InterchangeTGATranslator;
}

declare class InterchangeTIFFTranslator extends InterchangeTranslatorBase { 
	static Load(ResourceName: string): InterchangeTIFFTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeTIFFTranslator;
	static GetDefaultObject(): InterchangeTIFFTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTIFFTranslator;
	static C(Other: UObject | any): InterchangeTIFFTranslator;
}

declare class InterchangeUDIMTranslator extends InterchangeTranslatorBase { 
	UdimRegexPattern: string;
	static Load(ResourceName: string): InterchangeUDIMTranslator;
	static Find(Outer: UObject, ResourceName: string): InterchangeUDIMTranslator;
	static GetDefaultObject(): InterchangeUDIMTranslator;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeUDIMTranslator;
	static C(Other: UObject | any): InterchangeUDIMTranslator;
}

declare class InterchangeResultMeshWarning extends InterchangeResultWarning { 
	MeshName: string;
	static Load(ResourceName: string): InterchangeResultMeshWarning;
	static Find(Outer: UObject, ResourceName: string): InterchangeResultMeshWarning;
	static GetDefaultObject(): InterchangeResultMeshWarning;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeResultMeshWarning;
	static C(Other: UObject | any): InterchangeResultMeshWarning;
}

declare class InterchangeResultMeshError extends InterchangeResultError { 
	MeshName: string;
	static Load(ResourceName: string): InterchangeResultMeshError;
	static Find(Outer: UObject, ResourceName: string): InterchangeResultMeshError;
	static GetDefaultObject(): InterchangeResultMeshError;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeResultMeshError;
	static C(Other: UObject | any): InterchangeResultMeshError;
}

declare class InterchangeResultMeshWarning_Generic extends InterchangeResultMeshWarning { 
	text: string;
	static Load(ResourceName: string): InterchangeResultMeshWarning_Generic;
	static Find(Outer: UObject, ResourceName: string): InterchangeResultMeshWarning_Generic;
	static GetDefaultObject(): InterchangeResultMeshWarning_Generic;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeResultMeshWarning_Generic;
	static C(Other: UObject | any): InterchangeResultMeshWarning_Generic;
}

declare class InterchangeResultMeshError_Generic extends InterchangeResultMeshError { 
	text: string;
	static Load(ResourceName: string): InterchangeResultMeshError_Generic;
	static Find(Outer: UObject, ResourceName: string): InterchangeResultMeshError_Generic;
	static GetDefaultObject(): InterchangeResultMeshError_Generic;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeResultMeshError_Generic;
	static C(Other: UObject | any): InterchangeResultMeshError_Generic;
}

declare class InterchangeResultMeshWarning_TooManyUVs extends InterchangeResultMeshWarning { 
	ExcessUVs: number;
	static Load(ResourceName: string): InterchangeResultMeshWarning_TooManyUVs;
	static Find(Outer: UObject, ResourceName: string): InterchangeResultMeshWarning_TooManyUVs;
	static GetDefaultObject(): InterchangeResultMeshWarning_TooManyUVs;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeResultMeshWarning_TooManyUVs;
	static C(Other: UObject | any): InterchangeResultMeshWarning_TooManyUVs;
}

declare class InterchangeTextureWriter extends InterchangeWriterBase { 
	static Load(ResourceName: string): InterchangeTextureWriter;
	static Find(Outer: UObject, ResourceName: string): InterchangeTextureWriter;
	static GetDefaultObject(): InterchangeTextureWriter;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeTextureWriter;
	static C(Other: UObject | any): InterchangeTextureWriter;
}

declare type EInterchangeVertexColorImportOption = 'IVCIO_Replace' | 'IVCIO_Ignore' | 'IVCIO_Override' | 'IVCIO_MAX';
declare var EInterchangeVertexColorImportOption : { IVCIO_Replace:'IVCIO_Replace',IVCIO_Ignore:'IVCIO_Ignore',IVCIO_Override:'IVCIO_Override',IVCIO_MAX:'IVCIO_MAX', };
declare class InterchangeGenericAssetsPipeline extends InterchangePipelineBase { 
	bUseSourceNameForAsset: boolean;
	bImportLods: boolean;
	bBakeMeshes: boolean;
	VertexColorImportOption: EInterchangeVertexColorImportOption;
	VertexOverrideColor: Color;
	bImportStaticMeshes: boolean;
	bCombineStaticMeshes: boolean;
	Skeleton: Skeleton;
	bImportSkeletalMeshes: boolean;
	bCombineSkeletalMeshes: boolean;
	bImportMorphTargets: boolean;
	bCreatePhysicsAsset: boolean;
	PhysicsAsset: PhysicsAsset;
	bImportMaterials: boolean;
	bImportTextures: boolean;
	bDetectNormalMapTexture: boolean;
	bFlipNormalMapGreenChannel: boolean;
	FileExtensionsToImportAsLongLatCubemap: Set<string>;
	static Load(ResourceName: string): InterchangeGenericAssetsPipeline;
	static Find(Outer: UObject, ResourceName: string): InterchangeGenericAssetsPipeline;
	static GetDefaultObject(): InterchangeGenericAssetsPipeline;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeGenericAssetsPipeline;
	static C(Other: UObject | any): InterchangeGenericAssetsPipeline;
}

declare class InterchangeGenericLevelPipeline extends InterchangePipelineBase { 
	static Load(ResourceName: string): InterchangeGenericLevelPipeline;
	static Find(Outer: UObject, ResourceName: string): InterchangeGenericLevelPipeline;
	static GetDefaultObject(): InterchangeGenericLevelPipeline;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangeGenericLevelPipeline;
	static C(Other: UObject | any): InterchangeGenericLevelPipeline;
}

declare class InterchangeLodSceneNodeContainer { 
	SceneNodes: InterchangeSceneNode[];
	clone() : InterchangeLodSceneNodeContainer;
	static C(Other: UObject | any): InterchangeLodSceneNodeContainer;
}

declare class InterchangeMeshInstance { 
	MeshInstanceUid: string;
	LodGroupNode: InterchangeSceneNode;
	bReferenceSkinnedMesh: boolean;
	bReferenceBlendShape: boolean;
	SceneNodePerLodIndex: Map<number, InterchangeLodSceneNodeContainer>;
	ReferencingMeshGeometryUids: string[];
	clone() : InterchangeMeshInstance;
	static C(Other: UObject | any): InterchangeMeshInstance;
}

declare class InterchangeMeshGeometry { 
	MeshUid: string;
	MeshNode: InterchangeMeshNode;
	ReferencingMeshInstanceUids: string[];
	clone() : InterchangeMeshGeometry;
	static C(Other: UObject | any): InterchangeMeshGeometry;
}

declare class InterchangePipelineMeshesUtilities extends UObject { 
	static Load(ResourceName: string): InterchangePipelineMeshesUtilities;
	static Find(Outer: UObject, ResourceName: string): InterchangePipelineMeshesUtilities;
	static GetDefaultObject(): InterchangePipelineMeshesUtilities;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): InterchangePipelineMeshesUtilities;
	IsValidMeshInstanceUid(MeshInstanceUid: string): boolean;
	IsValidMeshGeometryUid(MeshGeometryUid: string): boolean;
	GetMeshInstanceSkeletonRootUid(MeshInstanceUid: string): string;
	GetMeshInstanceByUid(MeshInstanceUid: string): InterchangeMeshInstance;
	GetMeshGeometrySkeletonRootUid(MeshGeometryUid: string): string;
	GetMeshGeometryByUid(MeshGeometryUid: string): InterchangeMeshGeometry;
	GetAllStaticMeshInstance(MeshInstanceUids?: string[]): {MeshInstanceUids: string[]};
	GetAllStaticMeshGeometry(MeshGeometryUids?: string[]): {MeshGeometryUids: string[]};
	GetAllSkinnedMeshInstance(MeshInstanceUids?: string[]): {MeshInstanceUids: string[]};
	GetAllSkinnedMeshGeometry(MeshGeometryUids?: string[]): {MeshGeometryUids: string[]};
	GetAllMeshInstanceUidsUsingMeshGeometryUid(MeshGeometryUid: string,MeshInstanceUids?: string[]): {MeshInstanceUids: string[]};
	GetAllMeshInstanceUids(MeshInstanceUids?: string[]): {MeshInstanceUids: string[]};
	GetAllMeshGeometryNotInstanced(MeshGeometryUids?: string[]): {MeshGeometryUids: string[]};
	GetAllMeshGeometry(MeshGeometryUids?: string[]): {MeshGeometryUids: string[]};
	static CreateInterchangePipelineMeshesUtilities(BaseNodeContainer: InterchangeBaseNodeContainer): InterchangePipelineMeshesUtilities;
	static C(Other: UObject | any): InterchangePipelineMeshesUtilities;
}

declare class SubsystemBrowserConfigItem { 
	Name: string;
	bValue: boolean;
	clone() : SubsystemBrowserConfigItem;
	static C(Other: UObject | any): SubsystemBrowserConfigItem;
}

declare class SubsystemBrowserSettings extends UObject { 
	CategoryVisibilityState: SubsystemBrowserConfigItem[];
	TreeExpansionState: SubsystemBrowserConfigItem[];
	TableColumnVisibilityState: SubsystemBrowserConfigItem[];
	HorizontalSeparatorLocation: number;
	bEnableColoring: boolean;
	bShowHiddenProperties: boolean;
	bShowOnlyGameModules: boolean;
	static Load(ResourceName: string): SubsystemBrowserSettings;
	static Find(Outer: UObject, ResourceName: string): SubsystemBrowserSettings;
	static GetDefaultObject(): SubsystemBrowserSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SubsystemBrowserSettings;
	static C(Other: UObject | any): SubsystemBrowserSettings;
}

declare class MegascansSettings extends UObject { 
	bCreateFoliage: boolean;
	bApplyToSelection: boolean;
	static Load(ResourceName: string): MegascansSettings;
	static Find(Outer: UObject, ResourceName: string): MegascansSettings;
	static GetDefaultObject(): MegascansSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MegascansSettings;
	static C(Other: UObject | any): MegascansSettings;
}

declare class MaterialBlendSettings extends UObject { 
	BlendedMaterialName: string;
	BlendedMaterialPath: DirectoryPath;
	static Load(ResourceName: string): MaterialBlendSettings;
	static Find(Outer: UObject, ResourceName: string): MaterialBlendSettings;
	static GetDefaultObject(): MaterialBlendSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MaterialBlendSettings;
	static C(Other: UObject | any): MaterialBlendSettings;
}

declare class MaterialAssetSettings extends UObject { 
	MasterMaterial3d: string;
	MasterMaterialSurface: string;
	MasterMaterialPlant: string;
	static Load(ResourceName: string): MaterialAssetSettings;
	static Find(Outer: UObject, ResourceName: string): MaterialAssetSettings;
	static GetDefaultObject(): MaterialAssetSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MaterialAssetSettings;
	static C(Other: UObject | any): MaterialAssetSettings;
}

declare class MaterialPresetsSettings extends UObject { 
	MasterMaterial3d: Material;
	MasterMaterialSurface: Material;
	MasterMaterialPlant: Material;
	static Load(ResourceName: string): MaterialPresetsSettings;
	static Find(Outer: UObject, ResourceName: string): MaterialPresetsSettings;
	static GetDefaultObject(): MaterialPresetsSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MaterialPresetsSettings;
	static C(Other: UObject | any): MaterialPresetsSettings;
}

declare class AssetInfo { 
	Path: string;
	Version: string;
	clone() : AssetInfo;
	static C(Other: UObject | any): AssetInfo;
}

declare class VersionData { 
	Assets: AssetInfo[];
	clone() : VersionData;
	static C(Other: UObject | any): VersionData;
}

declare class VersionInfoHandler extends UObject { 
	CommonVersionData: VersionData;
	static Load(ResourceName: string): VersionInfoHandler;
	static Find(Outer: UObject, ResourceName: string): VersionInfoHandler;
	static GetDefaultObject(): VersionInfoHandler;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): VersionInfoHandler;
	static Get(): VersionInfoHandler;
	static C(Other: UObject | any): VersionInfoHandler;
}

declare class WebJSCallbackBase { 
	clone() : WebJSCallbackBase;
	static C(Other: UObject | any): WebJSCallbackBase;
}

declare class WebJSFunction extends WebJSCallbackBase { 
	clone() : WebJSFunction;
	static C(Other: UObject | any): WebJSFunction;
}

declare class BrowserBinding extends UObject { 
	static Load(ResourceName: string): BrowserBinding;
	static Find(Outer: UObject, ResourceName: string): BrowserBinding;
	static GetDefaultObject(): BrowserBinding;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): BrowserBinding;
	StartNodeProcess(): void;
	ShowLoginDialog(LoginUrl: string,ResponseCodeUrl: string): void;
	ShowDialog(Type: string,URL: string): void;
	SendSuccess(Value: string): void;
	SendFailure(Message: string): void;
	SaveAuthToken(Value: string): void;
	RestartNodeProcess(): void;
	OpenMegascansPluginSettings(): void;
	OpenExternalUrl(URL: string): void;
	OnExitCallback(OnExitJSCallback: WebJSFunction): void;
	OnDroppedCallback(OnDroppedJSCallback: WebJSFunction): void;
	OnDropDiscardedCallback(OnDropDiscardedJSCallback: WebJSFunction): void;
	Logout(): void;
	GetProjectPath(): string;
	GetAuthToken(): string;
	ExportDataToMSPlugin(Data: string): void;
	DragStarted(ImageUrl: string[],IDs: string[],Types: string[]): void;
	DialogSuccessCallback(DialogJSCallback: WebJSFunction): void;
	DialogFailCallback(DialogJSCallback: WebJSFunction): void;
	static C(Other: UObject | any): BrowserBinding;
}

declare class NodePort extends UObject { 
	static Load(ResourceName: string): NodePort;
	static Find(Outer: UObject, ResourceName: string): NodePort;
	static GetDefaultObject(): NodePort;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): NodePort;
	IsNodeRunning(): boolean;
	GetNodePort(): string;
	static C(Other: UObject | any): NodePort;
}

declare type EJavasriptTabActivationCause = 'UserClickedOnTab' | 'SetDirectly' | 'EJavasriptTabActivationCause_MAX';
declare var EJavasriptTabActivationCause : { UserClickedOnTab:'UserClickedOnTab',SetDirectly:'SetDirectly',EJavasriptTabActivationCause_MAX:'EJavasriptTabActivationCause_MAX', };
declare class JavascriptWorkspaceItem { 
	clone() : JavascriptWorkspaceItem;
	static C(Other: UObject | any): JavascriptWorkspaceItem;
	AddGroup(DisplayName: string): JavascriptWorkspaceItem;
	static AddGroup(Parent: JavascriptWorkspaceItem,DisplayName: string): JavascriptWorkspaceItem;
	static GetGroup(Name: string): JavascriptWorkspaceItem;
}

declare type EJavascriptTabRole = 'MajorTab' | 'PanelTab' | 'NomadTab' | 'DocumentTab' | 'EJavascriptTabRole_MAX';
declare var EJavascriptTabRole : { MajorTab:'MajorTab',PanelTab:'PanelTab',NomadTab:'NomadTab',DocumentTab:'DocumentTab',EJavascriptTabRole_MAX:'EJavascriptTabRole_MAX', };
declare class JavascriptEditorTab extends UObject { 
	OnSpawnTab: UnrealEngineDelegate<(Context: UObject) => Widget>;
	OnCloseTab: UnrealEngineDelegate<(Widget: Widget) => void>;
	OnTabActivatedCallback: UnrealEngineDelegate<(TabId: string, Cause: EJavasriptTabActivationCause) => void>;
	Group: JavascriptWorkspaceItem;
	TabId: string;
	DisplayName: string;
	Icon: JavascriptSlateIcon;
	bIsNomad: boolean;
	Role: EJavascriptTabRole;
	static Load(ResourceName: string): JavascriptEditorTab;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorTab;
	static GetDefaultObject(): JavascriptEditorTab;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorTab;
	ForceCommit(): void;
	Discard(): void;
	Commit(): void;
	CloseTab(Widget: Widget): void;
	static C(Other: UObject | any): JavascriptEditorTab;
}

declare class JavascriptUICommandInfo { 
	clone() : JavascriptUICommandInfo;
	static C(Other: UObject | any): JavascriptUICommandInfo;
	static GenericCommand(What: string): JavascriptUICommandInfo;
}

declare class JavascriptUICommand { 
	ID: string;
	FriendlyName: string;
	Description: string;
	DefaultChord: InputChord;
	ActionType: EJavasrciptUserInterfaceActionType;
	CommandInfo: JavascriptUICommandInfo;
	IconStyleName: string;
	clone() : JavascriptUICommand;
	static C(Other: UObject | any): JavascriptUICommand;
}

declare class JavascriptBindingContext { 
	clone() : JavascriptBindingContext;
	static C(Other: UObject | any): JavascriptBindingContext;
	Destroy(): void;
	UI_COMMAND_Function(Command: JavascriptUICommand,InTextSubNamespace: string): JavascriptUICommandInfo;
	static Destroy(Context: JavascriptBindingContext): void;
	static UI_COMMAND_Function(This: JavascriptBindingContext,Command: JavascriptUICommand,InTextSubNamespace: string): JavascriptUICommandInfo;
	static NewBindingContext(InContextName: string,InContextDesc: string,InContextParent: string,InStyleSetName: string): JavascriptBindingContext;
}

declare class JavascriptUICommandList { 
	clone() : JavascriptUICommandList;
	static C(Other: UObject | any): JavascriptUICommandList;
	CreateMenuBarBuilder(UFunction: JavascriptFunction): void;
	CreateMenuBuilder(bInShouldCloseWindowAfterMenuSelection: boolean,UFunction: JavascriptFunction): void;
	CreateToolbarBuilder(Orientation: EOrientation,UFunction: JavascriptFunction): void;
	ProcessCommandBindings_KeyEvent(InKeyEvent: KeyEvent): boolean;
	ProcessCommandBindings_PointerEvent(InMouseEvent: UPointerEvent): boolean;
	static CreateMenuBarBuilder(CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): void;
	static CreateMenuBuilder(CommandList: JavascriptUICommandList,bInShouldCloseWindowAfterMenuSelection: boolean,UFunction: JavascriptFunction): void;
	static CreateToolbarBuilder(CommandList: JavascriptUICommandList,Orientation: EOrientation,UFunction: JavascriptFunction): void;
	static ProcessCommandBindings_KeyEvent(CommandList: JavascriptUICommandList,InKeyEvent: KeyEvent): boolean;
	static ProcessCommandBindings_PointerEvent(CommandList: JavascriptUICommandList,InMouseEvent: UPointerEvent): boolean;
	static CreateUICommandList(): JavascriptUICommandList;
	static GetLevelEditorActions(): JavascriptUICommandList;
}

declare class JavascriptUICommands extends UObject { 
	OnExecuteAction: UnrealEngineDelegate<(ID: string) => void>;
	OnCanExecuteAction: UnrealEngineDelegate<(ID: string) => boolean>;
	OnIsActionChecked: UnrealEngineDelegate<(ID: string) => boolean>;
	OnIsActionButtonVisible: UnrealEngineDelegate<(ID: string) => boolean>;
	Commands: JavascriptUICommand[];
	ContextName: string;
	ContextDesc: string;
	ContextNameParent: string;
	StyleSetName: string;
	TextSubNamespace: string;
	CommandInfos: JavascriptUICommandInfo[];
	BindingContext: JavascriptBindingContext;
	static Load(ResourceName: string): JavascriptUICommands;
	static Find(Outer: UObject, ResourceName: string): JavascriptUICommands;
	static GetDefaultObject(): JavascriptUICommands;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptUICommands;
	Uninitialize(): void;
	Unbind(List: JavascriptUICommandList): void;
	Refresh(): void;
	Initialize(): void;
	GetAction(ID: string): JavascriptUICommandInfo;
	Discard(): void;
	Commit(): void;
	static BroadcastCommandsChanged(InContextName: string): void;
	Bind(List: JavascriptUICommandList): void;
	static C(Other: UObject | any): JavascriptUICommands;
}

declare type EJavascriptExtensionHook = 'Before' | 'After' | 'First' | 'EJavascriptExtensionHook_MAX';
declare var EJavascriptExtensionHook : { Before:'Before',After:'After',First:'First',EJavascriptExtensionHook_MAX:'EJavascriptExtensionHook_MAX', };
declare class JavascriptMenuExtension { 
	ExtensionHook: string;
	HookPosition: EJavascriptExtensionHook;
	clone() : JavascriptMenuExtension;
	static C(Other: UObject | any): JavascriptMenuExtension;
}

declare class JavascriptUIExtender extends UObject { 
	MenuExtensions: JavascriptMenuExtension[];
	ToolbarExtensions: JavascriptMenuExtension[];
	OnHook: UnrealEngineDelegate<(Hook: string) => void>;
	static Load(ResourceName: string): JavascriptUIExtender;
	static Find(Outer: UObject, ResourceName: string): JavascriptUIExtender;
	static GetDefaultObject(): JavascriptUIExtender;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptUIExtender;
	static GetTopCommandList(): JavascriptUICommandList;
	static EndSection(): void;
	static Bind(Commands: JavascriptUICommands): void;
	static BeginSection(Name: string,text: string): void;
	static AddToolBarButton(Commands: JavascriptUICommands,ID: string): void;
	static AddMenuSeparator(): void;
	static AddMenuEntry(Commands: JavascriptUICommands,ID: string): void;
	static C(Other: UObject | any): JavascriptUIExtender;
}

declare class JavascriptAssetEditorToolkit extends UObject { 
	ToolkitFName: string;
	Layout: string;
	BaseToolkitName: string;
	ToolkitName: string;
	WorldCentricTabColorScale: LinearColor;
	WorldCentricTabPrefix: string;
	Tabs: JavascriptEditorTab[];
	Commands: JavascriptUICommands;
	MenuExtender: JavascriptUIExtender;
	ToolbarExtender: JavascriptUIExtender;
	TestArray: number[];
	static Load(ResourceName: string): JavascriptAssetEditorToolkit;
	static Find(Outer: UObject, ResourceName: string): JavascriptAssetEditorToolkit;
	static GetDefaultObject(): JavascriptAssetEditorToolkit;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptAssetEditorToolkit;
	Refresh(): void;
	Discard(): void;
	Commit(): void;
	static C(Other: UObject | any): JavascriptAssetEditorToolkit;
}

declare class JavascriptAssetPicker extends Widget { 
	OnGetDefaultValue: UnrealEngineDelegate<() => UObject>;
	OnSetDefaultValue: UnrealEngineDelegate<(Value: string) => void>;
	CategoryObject: UObject;
	AllowedClasses: string;
	static Load(ResourceName: string): JavascriptAssetPicker;
	static Find(Outer: UObject, ResourceName: string): JavascriptAssetPicker;
	static GetDefaultObject(): JavascriptAssetPicker;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptAssetPicker;
	SetCategoryObject(InCategoryObject: UObject): void;
	SetAllowedClasses(InAllowedClasses: string): void;
	static C(Other: UObject | any): JavascriptAssetPicker;
}

declare class JavascriptAssetTypeActions extends UObject { 
	ActionsName: string;
	Color: Color;
	SupportedClass: UnrealEngineClass;
	Editor: JavascriptAssetEditorToolkit;
	Actions: JavascriptUIExtender;
	static Load(ResourceName: string): JavascriptAssetTypeActions;
	static Find(Outer: UObject, ResourceName: string): JavascriptAssetTypeActions;
	static GetDefaultObject(): JavascriptAssetTypeActions;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptAssetTypeActions;
	Refresh(): void;
	Discard(): void;
	Commit(): void;
	static C(Other: UObject | any): JavascriptAssetTypeActions;
}

declare class JavascriptColorPicker extends Widget { 
	OnColorChanged: UnrealEngineMulticastDelegate<(Color: LinearColor) => void>;
	SelectedColor: LinearColor;
	static Load(ResourceName: string): JavascriptColorPicker;
	static Find(Outer: UObject, ResourceName: string): JavascriptColorPicker;
	static GetDefaultObject(): JavascriptColorPicker;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptColorPicker;
	static C(Other: UObject | any): JavascriptColorPicker;
}

declare class JavascriptCommandlet extends Commandlet { 
	CmdLineTokens: string[];
	CmdLineSwitches: string[];
	static Load(ResourceName: string): JavascriptCommandlet;
	static Find(Outer: UObject, ResourceName: string): JavascriptCommandlet;
	static GetDefaultObject(): JavascriptCommandlet;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptCommandlet;
	static C(Other: UObject | any): JavascriptCommandlet;
}

declare class JavascriptCurveTableEditor extends Widget { 
	static Load(ResourceName: string): JavascriptCurveTableEditor;
	static Find(Outer: UObject, ResourceName: string): JavascriptCurveTableEditor;
	static GetDefaultObject(): JavascriptCurveTableEditor;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptCurveTableEditor;
	SetObject(UObject: CurveTable,bForceRefresh: boolean): void;
	Destruct(): void;
	Construct(): void;
	static C(Other: UObject | any): JavascriptCurveTableEditor;
}

declare class JavascriptWholeRowDetailCustomization extends UObject { 
	TypeName: string;
	CategoryName: string;
	CustomWidget: JavascriptSlateWidget;
	static Load(ResourceName: string): JavascriptWholeRowDetailCustomization;
	static Find(Outer: UObject, ResourceName: string): JavascriptWholeRowDetailCustomization;
	static GetDefaultObject(): JavascriptWholeRowDetailCustomization;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptWholeRowDetailCustomization;
	Unregister(): void;
	Register(): void;
	static C(Other: UObject | any): JavascriptWholeRowDetailCustomization;
}

declare class JavascriptDetailCustomization extends UObject { 
	TypeName: string;
	CategoryName: string;
	NameWidget: JavascriptSlateWidget;
	ValueWidget: JavascriptSlateWidget;
	static Load(ResourceName: string): JavascriptDetailCustomization;
	static Find(Outer: UObject, ResourceName: string): JavascriptDetailCustomization;
	static GetDefaultObject(): JavascriptDetailCustomization;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptDetailCustomization;
	Unregister(): void;
	Register(): void;
	static C(Other: UObject | any): JavascriptDetailCustomization;
}

declare class JavascriptEditorEngineLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): JavascriptEditorEngineLibrary;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorEngineLibrary;
	static GetDefaultObject(): JavascriptEditorEngineLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorEngineLibrary;
	static SetMaterial(Engine: EditorEngine,InModel: Model,Material: MaterialInterface,Surfaces: number[]): void;
	static SelectNone(Engine: EditorEngine,bNoteSelectionChange: boolean,bDeselectBSPSurfs: boolean,WarnAboutManyActors: boolean): void;
	static SelectGroup(Engine: EditorEngine,InGroupActor: GroupActor,bForceSelection: boolean,bInSelected: boolean,bNotify: boolean): void;
	static SelectComponent(Engine: EditorEngine,Component: ActorComponent,bInSelected: boolean,bNotify: boolean,bSelectEvenIfHidden: boolean): void;
	static SelectActor(Engine: EditorEngine,Actor: Actor,bInSelected: boolean,bNotify: boolean,bSelectEvenIfHidden: boolean,bForceRefresh: boolean): void;
	static RedrawAllViewports(Engine: EditorEngine,bInvalidateHitProxies: boolean): void;
	static RebuildStaticNavigableGeometry(Engine: EditorEngine,Level: Level): void;
	static RebuildLevel(Engine: EditorEngine,Level: Level): void;
	static GetSurfaces(Brush: Brush,Surfaces?: number[]): {Surfaces: number[]};
	static GetSelectedSet(Engine: EditorEngine,Class: UnrealEngineClass): USelection;
	static GetSelectedObjects(Engine: EditorEngine): USelection;
	static GetSelectedComponents(Engine: EditorEngine): USelection;
	static GetPIEWorld(Engine: Engine): World;
	static GetLongPackagePath(InPackage: Package): string;
	static GetEditorWorld(Engine: Engine): World;
	static FindBrushBuilder(Engine: EditorEngine,BrushBuilderClass: UnrealEngineClass): BrushBuilder;
	static Exec(Engine: EditorEngine,InWorld: World,Command: string,Out?: string): {Out: string, $: boolean};
	static DuplicateAsset(AssetName: string,PackagePath: string,OriginalObject: UObject): UObject;
	static DeleteObjectsUnchecked(ObjectsToDelete: UObject[]): number;
	static CanSelectActor(Engine: EditorEngine,Actor: Actor,bInSelected: boolean,bSelectEvenIfHidden: boolean,bWarnIfLevelLocked: boolean): boolean;
	static bspBrushCSG(Engine: EditorEngine,Actor: Brush,Model: Model,PolyFlags: number,BrushType: EBrushType,CSGOper: ECsgOper,bBuildBounds: boolean,bMergePolys: boolean,bReplaceNULLMaterialRefs: boolean,bShowProgressBar: boolean): number;
	static C(Other: UObject | any): JavascriptEditorEngineLibrary;
}

declare class JavascriptAssetData { 
	ObjectPath: string;
	PackageName: string;
	PackagePath: string;
	AssetName: string;
	AssetClass: string;
	ChunkIDs: number[];
	PackageFlags: number;
	clone() : JavascriptAssetData;
	static C(Other: UObject | any): JavascriptAssetData;
	GetAllTags(OutArray?: string[]): {OutArray: string[]};
	GetAsset(): UObject;
	GetClass(): UnrealEngineClass;
	GetPackage(): Package;
	GetTagValue(Name: string,OutValue?: string): {OutValue: string, $: boolean};
	IsAssetLoaded(): boolean;
	static GetAllTags(AssetData: JavascriptAssetData,OutArray?: string[]): {OutArray: string[]};
	static GetAsset(AssetData: JavascriptAssetData): UObject;
	static GetClass(AssetData: JavascriptAssetData): UnrealEngineClass;
	static GetPackage(AssetData: JavascriptAssetData): Package;
	static GetTagValue(AssetData: JavascriptAssetData,Name: string,OutValue?: string): {OutValue: string, $: boolean};
	static IsAssetLoaded(AssetData: JavascriptAssetData): boolean;
}

declare class JavascriptEditorGlobalDelegates extends UObject { 
	static Load(ResourceName: string): JavascriptEditorGlobalDelegates;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorGlobalDelegates;
	static GetDefaultObject(): JavascriptEditorGlobalDelegates;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorGlobalDelegates;
	WorldChange(): void;
	UnbindAll(): void;
	Unbind(Key: string): void;
	SurfProps(): void;
	SingleStepPIE(bIsSimulating: boolean): void;
	SelectedProps(): void;
	ResumePIE(bIsSimulating: boolean): void;
	RefreshPrimitiveStatsBrowser(): void;
	RefreshLayerBrowser(): void;
	RefreshEditor(): void;
	RefreshAllBrowsers(): void;
	RedrawAllViewports(): void;
	PropertySelectionChange(): void;
	PreSaveWorld_Friendly(SaveFlags: number,World: World): void;
	PreBeginPIE(bIsSimulating: boolean): void;
	PostSaveWorld_Friendly(SaveFlags: number,World: World,bSuccess: boolean): void;
	PostPIEStarted(bIsSimulating: boolean): void;
	PostLandscapeLayerUpdated(): void;
	OnShutdownPostPackagesSaved(): void;
	OnPathRemoved(Path: string): void;
	OnPathAdded(Path: string): void;
	OnObjectReimported(UObject: UObject): void;
	OnNewAssetCreated(InFactory: Factory): void;
	OnNewActorsDropped(DroppedObjects: UObject[],OutNewActors: Actor[]): void;
	OnMapOpened(Filename: string,bAsTemplate: boolean): void;
	OnMainFrameCreationFinished_Friendly(): void;
	OnLightingBuildStarted(): void;
	OnLightingBuildKept(): void;
	OnInMemoryAssetDeleted(InObject: UObject): void;
	OnInMemoryAssetCreated(InObject: UObject): void;
	OnGridSnappingChanged(bGridEnabled: boolean,GridSize: number): void;
	OnFocusViewportOnActors(Actors: Actor[]): void;
	OnFinishPickingBlueprintClass(InClass: UnrealEngineClass): void;
	OnFilesLoaded(): void;
	OnFileLoadProgressUpdated_Friendly(NumTotalAssets: number,NumAssetsProcessedByAssetRegistry: number,NumAssetsPendingDataLoad: number,bIsDiscoveringAssetFiles: boolean): void;
	OnEditPasteActorsEnd(): void;
	OnEditPasteActorsBegin(): void;
	OnEditorCameraMoved(ViewLocation: Vector,ViewRotation: Rotator,ViewportType: ELevelViewportType,ViewIndex: number): void;
	OnEditCutActorsEnd(): void;
	OnEditCutActorsBegin(): void;
	OnEditCopyActorsEnd(): void;
	OnEditCopyActorsBegin(): void;
	OnDuplicateActorsEnd(): void;
	OnDuplicateActorsBegin(): void;
	OnDollyPerspectiveCamera(Drag: Vector,ViewIndex: number): void;
	OnDeleteActorsEnd(): void;
	OnDeleteActorsBegin(): void;
	OnConfigureNewAssetProperties(InFactory: Factory): void;
	OnClassPackageLoadedOrUnloaded(): void;
	OnBlueprintReinstanced(): void;
	OnBlueprintPreCompile(Blueprint: Blueprint): void;
	OnBlueprintCompiled(): void;
	OnAssetsPreDelete(Assets: UObject[]): void;
	OnAssetsDeleted(Classes: UnrealEngineClass[]): void;
	OnAssetRenamed_Friendly(AssetData: JavascriptAssetData,Name: string): void;
	OnAssetRemoved_Friendly(AssetData: JavascriptAssetData): void;
	OnAssetReimport(InCreatedObject: UObject): void;
	OnAssetPreImport_Friendly(InFactory: Factory,InClass: UnrealEngineClass,InParent: UObject,Name: string,Type: string): void;
	OnAssetPostImport(InFactory: Factory,InCreatedObject: UObject): void;
	OnAssetAdded_Friendly(AssetData: JavascriptAssetData): void;
	OnApplyObjectToActor(ObjectToApply: UObject,Actor: Actor): void;
	OnAddLevelToWorld(Level: Level): void;
	OnActionAxisMappingsChanged(): void;
	NewCurrentLevel(): void;
	MapChange_Friendly(MapChangeFlags: number): void;
	LoadSelectedAssetsIfNeeded(): void;
	LayerChange(): void;
	FitTextureToSurface(World: World): void;
	EndPlayMapDelegate(): void;
	EndPIE(bIsSimulating: boolean): void;
	DisplayLoadErrors(): void;
	CleanseEditor(): void;
	ChangeEditorMode(NewMode: string): void;
	Bind(Key: string): void;
	BeginPIE(bIsSimulating: boolean): void;
	ActorPropertiesChange(): void;
	static C(Other: UObject | any): JavascriptEditorGlobalDelegates;
}

declare class JavascriptEditorInputProcessor extends UObject { 
	static Load(ResourceName: string): JavascriptEditorInputProcessor;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorInputProcessor;
	static GetDefaultObject(): JavascriptEditorInputProcessor;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorInputProcessor;
	UnRegister(): void;
	Register(): void;
	HandleMouseMoveEvent(InPointerEvent: UPointerEvent): boolean;
	HandleKeyUpEvent(InKeyEvent: KeyEvent): boolean;
	HandleKeyDownEvent(InKeyEvent: KeyEvent): boolean;
	HandleAnalogInputEvent(InKeyEvent: AnalogInputEvent): boolean;
	Activate(bEnable: boolean): void;
	static C(Other: UObject | any): JavascriptEditorInputProcessor;
}

declare class JavascriptExtensionBase { 
	clone() : JavascriptExtensionBase;
	static C(Other: UObject | any): JavascriptExtensionBase;
}

declare class JavascriptMenuBuilder { 
	clone() : JavascriptMenuBuilder;
	static C(Other: UObject | any): JavascriptMenuBuilder;
	AddComboButton(UObject?: JavascriptComboButtonContext,EditingObject?: UObject): {Builder: JavascriptMenuBuilder};
	AddMenuByCommands(UICommands?: JavascriptUICommands): {Builder: JavascriptMenuBuilder};
	AddMenuEntry(UObject?: JavascriptMenuContext): {Builder: JavascriptMenuBuilder};
	AddPullDownMenu(InMenuLabel?: string,InToolTip?: string,InPullDownMenu?: JavascriptFunction,InExtensionHook?: string,InTutorialHighlightName?: string): {MenuBuilder: JavascriptMenuBuilder};
	AddSeparator(): {Builder: JavascriptMenuBuilder};
	AddSubMenu(Label?: string,Tooltip?: string,bInOpenSubMenuOnClick?: boolean,UFunction?: JavascriptFunction): {Builder: JavascriptMenuBuilder};
	AddToolBarButton(CommandInfo?: JavascriptUICommandInfo): {Builder: JavascriptMenuBuilder};
	AddToolBarButtonByContext(Context?: JavascriptToolbarButtonContext,EditingObject?: UObject): {Builder: JavascriptMenuBuilder};
	AddWidget(Widget?: Widget,Label?: string,bNoIndent?: boolean,InTutorialHighlightName?: string,bSearchable?: boolean): {Builder: JavascriptMenuBuilder};
	BeginSection(InExtensionHook?: string,MenuHeadingText?: string): {Builder: JavascriptMenuBuilder};
	EndSection(): {Builder: JavascriptMenuBuilder};
	PopCommandList(): {Builder: JavascriptMenuBuilder};
	PushCommandList(List?: JavascriptUICommandList): {Builder: JavascriptMenuBuilder};
	static AddComboButton(Builder?: JavascriptMenuBuilder,UObject?: JavascriptComboButtonContext,EditingObject?: UObject): {Builder: JavascriptMenuBuilder};
	static AddMenuByCommands(Builder?: JavascriptMenuBuilder,UICommands?: JavascriptUICommands): {Builder: JavascriptMenuBuilder};
	static AddMenuEntry(Builder?: JavascriptMenuBuilder,UObject?: JavascriptMenuContext): {Builder: JavascriptMenuBuilder};
	static AddPullDownMenu(MenuBuilder?: JavascriptMenuBuilder,InMenuLabel?: string,InToolTip?: string,InPullDownMenu?: JavascriptFunction,InExtensionHook?: string,InTutorialHighlightName?: string): {MenuBuilder: JavascriptMenuBuilder};
	static AddSeparator(Builder?: JavascriptMenuBuilder): {Builder: JavascriptMenuBuilder};
	static AddSubMenu(Builder?: JavascriptMenuBuilder,Label?: string,Tooltip?: string,bInOpenSubMenuOnClick?: boolean,UFunction?: JavascriptFunction): {Builder: JavascriptMenuBuilder};
	static AddToolBarButton(Builder?: JavascriptMenuBuilder,CommandInfo?: JavascriptUICommandInfo): {Builder: JavascriptMenuBuilder};
	static AddToolBarButtonByContext(Builder?: JavascriptMenuBuilder,Context?: JavascriptToolbarButtonContext,EditingObject?: UObject): {Builder: JavascriptMenuBuilder};
	static AddWidget(Builder?: JavascriptMenuBuilder,Widget?: Widget,Label?: string,bNoIndent?: boolean,InTutorialHighlightName?: string,bSearchable?: boolean): {Builder: JavascriptMenuBuilder};
	static BeginSection(Builder?: JavascriptMenuBuilder,InExtensionHook?: string,MenuHeadingText?: string): {Builder: JavascriptMenuBuilder};
	static EndSection(Builder?: JavascriptMenuBuilder): {Builder: JavascriptMenuBuilder};
	static PopCommandList(Builder?: JavascriptMenuBuilder): {Builder: JavascriptMenuBuilder};
	static PushCommandList(Builder?: JavascriptMenuBuilder,List?: JavascriptUICommandList): {Builder: JavascriptMenuBuilder};
}

declare class JavascriptExtender { 
	clone() : JavascriptExtender;
	static C(Other: UObject | any): JavascriptExtender;
	AddMenubarExtension(ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	AddMenuExtension(ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	AddToolBarExtension(ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	Apply(ExtensionHook: string,HookPosition: EJavascriptExtensionHook,MenuBuilder?: JavascriptMenuBuilder): {MenuBuilder: JavascriptMenuBuilder};
	RemoveExtension(Extension: JavascriptExtensionBase): void;
	static AddMenubarExtension(Extender: JavascriptExtender,ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	static AddMenuExtension(Extender: JavascriptExtender,ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	static AddToolBarExtension(Extender: JavascriptExtender,ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	static Apply(Extender: JavascriptExtender,ExtensionHook: string,HookPosition: EJavascriptExtensionHook,MenuBuilder?: JavascriptMenuBuilder): {MenuBuilder: JavascriptMenuBuilder};
	static RemoveExtension(Extender: JavascriptExtender,Extension: JavascriptExtensionBase): void;
	static Combine(Extenders: JavascriptExtender[]): JavascriptExtender;
}

declare class JavascriptLazyExtenderDelegates extends UObject { 
	GetExtender: UnrealEngineDelegate<(List: JavascriptUICommandList, EditingObjects: UObject[]) => JavascriptExtender>;
	static Load(ResourceName: string): JavascriptLazyExtenderDelegates;
	static Find(Outer: UObject, ResourceName: string): JavascriptLazyExtenderDelegates;
	static GetDefaultObject(): JavascriptLazyExtenderDelegates;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptLazyExtenderDelegates;
	static C(Other: UObject | any): JavascriptLazyExtenderDelegates;
}

declare type EJavascriptRHIFeatureLevel = 'ES2' | 'ES3_1' | 'SM4' | 'SM5' | 'Num' | 'EJavascriptRHIFeatureLevel_MAX';
declare var EJavascriptRHIFeatureLevel : { ES2:'ES2',ES3_1:'ES3_1',SM4:'SM4',SM5:'SM5',Num:'Num',EJavascriptRHIFeatureLevel_MAX:'EJavascriptRHIFeatureLevel_MAX', };
declare class JavascriptPDI { 
	clone() : JavascriptPDI;
	static C(Other: UObject | any): JavascriptPDI;
	DrawArc(Base: Vector,X: Vector,Y: Vector,MinAngle: number,MaxAngle: number,Radius: number,Sections: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	DrawCircle(Base: Vector,X: Vector,Y: Vector,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawConnectedArrow(ArrowToWorld: Transform,Color: LinearColor,ArrowHeight: number,ArrowWidth: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,NumSpokes: number): void;
	DrawDashedLine(Start: Vector,End: Vector,Color: LinearColor,DashSize: number,DepthPriority: ESceneDepthPriorityGroup,DepthBias: number): void;
	DrawDirectionalArrow(ArrowToWorld: Transform,InColor: LinearColor,Length: number,ArrowSize: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number): void;
	DrawOrientedWireBox(Base: Vector,X: Vector,Y: Vector,Z: Vector,Extent: Vector,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawPolygon(Verts: Vector[],InColor: LinearColor,DepthPriority: ESceneDepthPriorityGroup,RHIFeatureLevel: EJavascriptRHIFeatureLevel): void;
	DrawWireBox(Box: Box,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawWireBox2(Matrix: Transform,Box: Box,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawWireCapsule(Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawWireChoppedCone(Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,TopRadius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup): void;
	DrawWireCone(Verts?: Vector[],Transform?: Transform,ConeRadius?: number,ConeAngle?: number,ConeSides?: number,Color?: LinearColor,DepthPriority?: ESceneDepthPriorityGroup,Thickness?: number,DepthBias?: number,bScreenSpace?: boolean): {Verts: Vector[]};
	DrawWireCylinder(Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawWireDiamond(Transform: Transform,Size: number,InColor: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	DrawWireSphere(Base: Vector,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawWireSphere2(Transform: Transform,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawWireSphereAutoSides(Base: Vector,Color: LinearColor,Radius: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawWireSphereAutoSides2(Transform: Transform,Color: LinearColor,Radius: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	DrawWireSphereCappedCone(Transform: Transform,ConeRadius: number,ConeAngle: number,ConeSides: number,ArcFrequency: number,CapSegments: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	DrawWireStar(position: Vector,Size: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	SetHitProxy(Name: string): void;
	static DrawArc(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,MinAngle: number,MaxAngle: number,Radius: number,Sections: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	static DrawCircle(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawConnectedArrow(PDI: JavascriptPDI,ArrowToWorld: Transform,Color: LinearColor,ArrowHeight: number,ArrowWidth: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,NumSpokes: number): void;
	static DrawDashedLine(PDI: JavascriptPDI,Start: Vector,End: Vector,Color: LinearColor,DashSize: number,DepthPriority: ESceneDepthPriorityGroup,DepthBias: number): void;
	static DrawDirectionalArrow(PDI: JavascriptPDI,ArrowToWorld: Transform,InColor: LinearColor,Length: number,ArrowSize: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number): void;
	static DrawOrientedWireBox(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Z: Vector,Extent: Vector,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawPolygon(PDI: JavascriptPDI,Verts: Vector[],InColor: LinearColor,DepthPriority: ESceneDepthPriorityGroup,RHIFeatureLevel: EJavascriptRHIFeatureLevel): void;
	static DrawWireBox(PDI: JavascriptPDI,Box: Box,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireBox2(PDI: JavascriptPDI,Matrix: Transform,Box: Box,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireCapsule(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireChoppedCone(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,TopRadius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup): void;
	static DrawWireCone(PDI: JavascriptPDI,Verts?: Vector[],Transform?: Transform,ConeRadius?: number,ConeAngle?: number,ConeSides?: number,Color?: LinearColor,DepthPriority?: ESceneDepthPriorityGroup,Thickness?: number,DepthBias?: number,bScreenSpace?: boolean): {Verts: Vector[]};
	static DrawWireCylinder(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireDiamond(PDI: JavascriptPDI,Transform: Transform,Size: number,InColor: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	static DrawWireSphere(PDI: JavascriptPDI,Base: Vector,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireSphere2(PDI: JavascriptPDI,Transform: Transform,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireSphereAutoSides(PDI: JavascriptPDI,Base: Vector,Color: LinearColor,Radius: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireSphereAutoSides2(PDI: JavascriptPDI,Transform: Transform,Color: LinearColor,Radius: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireSphereCappedCone(PDI: JavascriptPDI,Transform: Transform,ConeRadius: number,ConeAngle: number,ConeSides: number,ArcFrequency: number,CapSegments: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	static DrawWireStar(PDI: JavascriptPDI,position: Vector,Size: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	static SetHitProxy(PDI: JavascriptPDI,Name: string): void;
}

declare class JavascriptExtensibilityManager { 
	clone() : JavascriptExtensibilityManager;
	static C(Other: UObject | any): JavascriptExtensibilityManager;
	AddExtender(Extender: JavascriptExtender): void;
	AddLazyExtender(Delegates: JavascriptLazyExtenderDelegates): void;
	RemoveAllLazyExtender(): void;
	RemoveExtender(Extender: JavascriptExtender): void;
	static AddExtender(Manager: JavascriptExtensibilityManager,Extender: JavascriptExtender): void;
	static AddLazyExtender(Manager: JavascriptExtensibilityManager,Delegates: JavascriptLazyExtenderDelegates): void;
	static RemoveAllLazyExtender(Manager: JavascriptExtensibilityManager): void;
	static RemoveExtender(Manager: JavascriptExtensibilityManager,Extender: JavascriptExtender): void;
	static GetMenuExtensibilityManager(What: string): JavascriptExtensibilityManager;
	static GetToolBarExtensibilityManager(What: string): JavascriptExtensibilityManager;
}

declare class JavascriptViewportClick { 
	clone() : JavascriptViewportClick;
	static C(Other: UObject | any): JavascriptViewportClick;
	GetClickPos(): IntPoint;
	GetDirection(): Vector;
	GetEvent(): EInputEvent;
	GetKey(): Key;
	GetOrigin(): Vector;
	IsAltDown(): boolean;
	IsControlDown(): boolean;
	IsShiftDown(): boolean;
	static GetClickPos(Click: JavascriptViewportClick): IntPoint;
	static GetDirection(Click: JavascriptViewportClick): Vector;
	static GetEvent(Click: JavascriptViewportClick): EInputEvent;
	static GetKey(Click: JavascriptViewportClick): Key;
	static GetOrigin(Click: JavascriptViewportClick): Vector;
	static IsAltDown(Click: JavascriptViewportClick): boolean;
	static IsControlDown(Click: JavascriptViewportClick): boolean;
	static IsShiftDown(Click: JavascriptViewportClick): boolean;
}

declare class JavascriptHitProxy { 
	clone() : JavascriptHitProxy;
	static C(Other: UObject | any): JavascriptHitProxy;
	GetActor(): Actor;
	GetName(): string;
	static GetActor(Proxy: JavascriptHitProxy): Actor;
	static GetName(Proxy: JavascriptHitProxy): string;
}

declare type EJavascriptMessageSeverity = 'CriticalError' | 'Error' | 'PerformanceWarning' | 'Warning' | 'Info' | 'EJavascriptMessageSeverity_MAX';
declare var EJavascriptMessageSeverity : { CriticalError:'CriticalError',Error:'Error',PerformanceWarning:'PerformanceWarning',Warning:'Warning',Info:'Info',EJavascriptMessageSeverity_MAX:'EJavascriptMessageSeverity_MAX', };
declare class JavascriptEditorLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): JavascriptEditorLibrary;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorLibrary;
	static GetDefaultObject(): JavascriptEditorLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorLibrary;
	static UpdateModelComponents(Level: Level): void;
	static ToggleSelect(USelection: USelection,InObject: UObject): void;
	static ToggleIsExecuteTestModePIE(): boolean;
	static SetIsTemporarilyHiddenInEditor(Actor: Actor,bIsHidden: boolean): void;
	static SetHitProxy(PDI: JavascriptPDI,Name: string): void;
	static SetHeightmapDataFromMemory(LandscapeInfo: LandscapeInfo,MinX: number,MinY: number,MaxX: number,MaxY: number): void;
	static SetFolderPath_Recursively(Actor: Actor,NewFolderPath: string): void;
	static SetFolderPath(Actor: Actor,NewFolderPath: string): void;
	static SetAlphamapDataFromMemory(LandscapeInfo: LandscapeInfo,LayerInfo: LandscapeLayerInfoObject,MinX: number,MinY: number,MaxX: number,MaxY: number,PaintingRestriction: ELandscapeLayerPaintingRestriction): void;
	static SetActorLocation(Actor: Actor,NewLocation: Vector,bSweep: boolean,SweepHitResult?: HitResult,bTeleport?: boolean): {SweepHitResult: HitResult, $: boolean};
	static SetActorLabelUnique(Actor: Actor,NewActorLabel: string,InExistingActorLabels: string[]): void;
	static SetActorLabel(Actor: Actor,NewActorLabel: string,bMarkDirty: boolean): void;
	static Select(USelection: USelection,InObject: UObject): void;
	static SavePackage(Package: Package,Filename: string): boolean;
	static RequestEndPlayMapInPIE(): void;
	static ReplaceAnimNotifyClass(Sequence: AnimSequenceBase,NotifyName: string,NewNotifyName: string,NewNotifyClass: UObject): number;
	static RemoveLevelInstance(World: World): void;
	static RemoveExtender(Manager: JavascriptExtensibilityManager,Extender: JavascriptExtender): void;
	static RemoveComponentFromBlueprint(Blueprint: Blueprint,RemoveComponent: ActorComponent,bPromoteChildren: boolean): void;
	static RemoveAllLazyExtender(Manager: JavascriptExtensibilityManager): void;
	static PostEditChange(InObject: UObject): void;
	static OpenPopupWindow(Widget: Widget,PopupDesiredSize: Vector2D,HeadingText: string): void;
	static OpenFileDialog(WindowHandle: JavascriptWindow,DialogTitle: string,DefaultPath: string,DefaultFile: string,FileTypes: string,Flags: number,OutFilenames?: string[]): {OutFilenames: string[], $: boolean};
	static OpenEditorForAssetByPath(AssetPathName: string,ObjectName: string): void;
	static OpenEditorForAsset(Asset: UObject): boolean;
	static OpenDirectoryDialog(WindowHandle: JavascriptWindow,DialogTitle: string,DefaultPath: string,OutFolderName?: string): {OutFolderName: string, $: boolean};
	static NotifyUpdateCurveTable(InCurveTable: CurveTable): void;
	static ModifyObject(UObject: UObject,bAlwaysMarkDirty: boolean): void;
	static MarkPackageDirty(InObject: UObject): boolean;
	static LoadImageFromDiskAsync(ImagePath: string,Callback: AsyncTaskDownloadImage): boolean;
	static LoadFileToString(Path: string,Data?: string): {Data: string, $: boolean};
	static LoadFileToIntArray(Path: string,FileData?: number[]): {FileData: number[], $: boolean};
	static IsShiftDown(Click: JavascriptViewportClick): boolean;
	static IsControlDown(Click: JavascriptViewportClick): boolean;
	static IsAssetLoaded(AssetData: JavascriptAssetData): boolean;
	static IsAltDown(Click: JavascriptViewportClick): boolean;
	static IsActorLabelEditable(Actor: Actor): boolean;
	static IsActive(Transactor: Transactor): boolean;
	static InvalidateModelGeometry(World: World,InLevel: Level): void;
	static HasMetaData(Field: Field,Key: string): boolean;
	static GetUniqueID(InObject: UObject): number;
	static GetTransaction(Transactor: Transactor,QueueIndex: number): JavascriptTransaction;
	static GetToolBarExtensibilityManager(What: string): JavascriptExtensibilityManager;
	static GetTitle(Transaction: JavascriptTransaction): string;
	static GetTagValue(AssetData: JavascriptAssetData,Name: string,OutValue?: string): {OutValue: string, $: boolean};
	static GetSelectedObjects(USelection: USelection,Out?: UObject[]): {Out: UObject[], $: number};
	static GetRootWindow(): JavascriptSlateWidget;
	static GetQueueLength(Transactor: Transactor): number;
	static GetPrimaryObject(Transaction: JavascriptTransaction): UObject;
	static GetParentClassOfBlueprint(Blueprint: Blueprint): UnrealEngineClass;
	static GetPackage(AssetData: JavascriptAssetData): Package;
	static GetOrigin(Click: JavascriptViewportClick): Vector;
	static GetName(Proxy: JavascriptHitProxy): string;
	static GetMenuExtensibilityManager(What: string): JavascriptExtensibilityManager;
	static GetLevelEditorActions(): JavascriptUICommandList;
	static GetLayerInfoByName(LandscapeInfo: LandscapeInfo,LayerName: string,Owner: LandscapeProxy): LandscapeLayerInfoObject;
	static GetLandscapeInfo(Landscape: Landscape,bSpawnNewActor: boolean): LandscapeInfo;
	static GetLandscapeExtent(LandscapeInfo: LandscapeInfo,MinX?: number,MinY?: number,MaxX?: number,MaxY?: number): {MinX: number, MinY: number, MaxX: number, MaxY: number, $: boolean};
	static GetKeyNameByKeyEvent(Event: KeyEvent): string;
	static GetKey(Click: JavascriptViewportClick): Key;
	static GetIsShiftDownByKeyEvent(Event: KeyEvent): boolean;
	static GetIsExecuteTestModePIE(): boolean;
	static GetIsControlDownByKeyEvent(Event: KeyEvent): boolean;
	static GetIsAltDownByKeyEvent(Event: KeyEvent): boolean;
	static GetHeightmapDataToMemory(LandscapeInfo: LandscapeInfo,MinX: number,MinY: number,MaxX: number,MaxY: number): void;
	static GetGroup(Name: string): JavascriptWorkspaceItem;
	static GetFolderPath(Actor: Actor): string;
	static GetEvent(Click: JavascriptViewportClick): EInputEvent;
	static GetEngine(): EditorEngine;
	static GetEditorPlayWorld(): World;
	static GetDirection(Click: JavascriptViewportClick): Vector;
	static GetDataTableAsJSON(InDataTable: DataTable,InDTExportFlags: number): string;
	static GetContext(Transaction: JavascriptTransaction): string;
	static GetClickPos(Click: JavascriptViewportClick): IntPoint;
	static GetClass(AssetData: JavascriptAssetData): UnrealEngineClass;
	static GetAssetsByType(Types: string[],bRecursiveClasses: boolean): AssetData[];
	static GetAsset(AssetData: JavascriptAssetData): UObject;
	static GetAlphamapDataToMemory(LandscapeInfo: LandscapeInfo,LayerInfo: LandscapeLayerInfoObject,MinX: number,MinY: number,MaxX: number,MaxY: number): void;
	static GetAllTags(AssetData: JavascriptAssetData,OutArray?: string[]): {OutArray: string[]};
	static GetActorRotation(Actor: Actor): Rotator;
	static GetActorLocation(Actor: Actor): Vector;
	static GetActorLabel(Actor: Actor): string;
	static GetActor(Proxy: JavascriptHitProxy): Actor;
	static FindWorldInPackage(Package: Package): World;
	static ExportNavigation(InWorld: World,Path: string): string;
	static EditorDestroyActor(World: World,Actor: Actor,bShouldModifyLevel: boolean): boolean;
	static EditorAddModalWindow(Widget: JavascriptSlateWidget): void;
	static DrawWireStar(PDI: JavascriptPDI,position: Vector,Size: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	static DrawWireSphereCappedCone(PDI: JavascriptPDI,Transform: Transform,ConeRadius: number,ConeAngle: number,ConeSides: number,ArcFrequency: number,CapSegments: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	static DrawWireSphereAutoSides2(PDI: JavascriptPDI,Transform: Transform,Color: LinearColor,Radius: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireSphereAutoSides(PDI: JavascriptPDI,Base: Vector,Color: LinearColor,Radius: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireSphere2(PDI: JavascriptPDI,Transform: Transform,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireSphere(PDI: JavascriptPDI,Base: Vector,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireDiamond(PDI: JavascriptPDI,Transform: Transform,Size: number,InColor: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	static DrawWireCylinder(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireCone(PDI: JavascriptPDI,Verts?: Vector[],Transform?: Transform,ConeRadius?: number,ConeAngle?: number,ConeSides?: number,Color?: LinearColor,DepthPriority?: ESceneDepthPriorityGroup,Thickness?: number,DepthBias?: number,bScreenSpace?: boolean): {Verts: Vector[]};
	static DrawWireChoppedCone(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,TopRadius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup): void;
	static DrawWireCapsule(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Z: Vector,Color: LinearColor,Radius: number,HalfHeight: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireBox2(PDI: JavascriptPDI,Matrix: Transform,Box: Box,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawWireBox(PDI: JavascriptPDI,Box: Box,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawPolygon(PDI: JavascriptPDI,Verts: Vector[],InColor: LinearColor,DepthPriority: ESceneDepthPriorityGroup,RHIFeatureLevel: EJavascriptRHIFeatureLevel): void;
	static DrawOrientedWireBox(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Z: Vector,Extent: Vector,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawDirectionalArrow(PDI: JavascriptPDI,ArrowToWorld: Transform,InColor: LinearColor,Length: number,ArrowSize: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number): void;
	static DrawDashedLine(PDI: JavascriptPDI,Start: Vector,End: Vector,Color: LinearColor,DashSize: number,DepthPriority: ESceneDepthPriorityGroup,DepthBias: number): void;
	static DrawConnectedArrow(PDI: JavascriptPDI,ArrowToWorld: Transform,Color: LinearColor,ArrowHeight: number,ArrowWidth: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,NumSpokes: number): void;
	static DrawCircle(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,Color: LinearColor,Radius: number,NumSides: number,DepthPriority: ESceneDepthPriorityGroup,Thickness: number,DepthBias: number,bScreenSpace: boolean): void;
	static DrawArc(PDI: JavascriptPDI,Base: Vector,X: Vector,Y: Vector,MinAngle: number,MaxAngle: number,Radius: number,Sections: number,Color: LinearColor,DepthPriority: ESceneDepthPriorityGroup): void;
	static DeselectAll(USelection: USelection,InClass: UnrealEngineClass): void;
	static Deselect(USelection: USelection,InObject: UObject): void;
	static DeletePackage(Package: Package): boolean;
	static CreatePropertyEditorToolkit(ObjectsForPropertiesMenu: UObject[]): void;
	static CreateLogListingWidget(InLogName: string): JavascriptSlateWidget;
	static CreateLogListing(InLogName: string,InLabel: string): void;
	static ConditionalBeginDestroybyUObject(TargetObject: UObject): boolean;
	static CompileBlueprint(Blueprint: Blueprint): void;
	static ClearActorLabel(Actor: Actor): void;
	static BroadcastHotReload(): void;
	static BroadcastAssetCreated(NewAsset: UObject): void;
	static AddWhitelistedObject(InObject: UObject): void;
	static AddRichCurve(InCurveTable: CurveTable,Key: string,InCurve: RichCurve): void;
	static AddLogListingMessage(InLogName: string,InSeverity: EJavascriptMessageSeverity,LogText: string): void;
	static AddLazyExtender(Manager: JavascriptExtensibilityManager,Delegates: JavascriptLazyExtenderDelegates): void;
	static AddGroup(Parent: JavascriptWorkspaceItem,DisplayName: string): JavascriptWorkspaceItem;
	static AddExtender(Manager: JavascriptExtensibilityManager,Extender: JavascriptExtender): void;
	static AddComponentsToBlueprint(Blueprint: Blueprint,Components: ActorComponent[],bHarvesting: boolean,OptionalNewRootComponent: ActorComponent,bKeepMobility: boolean): void;
	static C(Other: UObject | any): JavascriptEditorLibrary;
}

declare class JavascriptEditorPopupWindow extends UObject { 
	Widget: Widget;
	static Load(ResourceName: string): JavascriptEditorPopupWindow;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorPopupWindow;
	static GetDefaultObject(): JavascriptEditorPopupWindow;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorPopupWindow;
	Open(Heading: string,DesiredSize: Vector2D): boolean;
	OnDismissed(): void;
	static C(Other: UObject | any): JavascriptEditorPopupWindow;
}

declare class JavascriptEditorTabManager extends Widget { 
	Layout: string;
	Tabs: JavascriptEditorTab[];
	static Load(ResourceName: string): JavascriptEditorTabManager;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorTabManager;
	static GetDefaultObject(): JavascriptEditorTabManager;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorTabManager;
	InvokeTab(SearchForTabId: string): void;
	InsertNewTab(PlaceholderId: string,SearchForTabId: string,NewTab: JavascriptEditorTab): void;
	static C(Other: UObject | any): JavascriptEditorTabManager;
}

declare class JavascriptEditorTick extends UObject { 
	OnTick: UnrealEngineDelegate<(DeltaSeconds: number) => void>;
	static Load(ResourceName: string): JavascriptEditorTick;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorTick;
	static GetDefaultObject(): JavascriptEditorTick;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorTick;
	GetEngine(): EditorEngine;
	ForceTick(DeltaTime: number): void;
	static C(Other: UObject | any): JavascriptEditorTick;
}

declare class JavascriptEditorToolbar extends Widget { 
	OnHook: UnrealEngineDelegate<() => JavascriptMenuBuilder>;
	static Load(ResourceName: string): JavascriptEditorToolbar;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorToolbar;
	static GetDefaultObject(): JavascriptEditorToolbar;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorToolbar;
	static C(Other: UObject | any): JavascriptEditorToolbar;
}

declare class JavascriptInputEventState { 
	clone() : JavascriptInputEventState;
	static C(Other: UObject | any): JavascriptInputEventState;
	GetInputEvent(): EInputEvent;
	GetKey(): Key;
	IsAltButtonEvent(): boolean;
	IsAltButtonPressed(): boolean;
	IsAnyMouseButtonDown(): boolean;
	IsButtonPressed(InKey: Key): boolean;
	IsCtrlButtonEvent(): boolean;
	IsCtrlButtonPressed(): boolean;
	IsLeftMouseButtonPressed(): boolean;
	IsMiddleMouseButtonPressed(): boolean;
	IsMouseButtonEvent(): boolean;
	IsRightMouseButtonPressed(): boolean;
	IsShiftButtonEvent(): boolean;
	IsShiftButtonPressed(): boolean;
	IsSpaceBarPressed(): boolean;
	static GetInputEvent(InputEvent: JavascriptInputEventState): EInputEvent;
	static GetKey(InputEvent: JavascriptInputEventState): Key;
	static IsAltButtonEvent(InputEvent: JavascriptInputEventState): boolean;
	static IsAltButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsAnyMouseButtonDown(InputEvent: JavascriptInputEventState): boolean;
	static IsButtonPressed(InputEvent: JavascriptInputEventState,InKey: Key): boolean;
	static IsCtrlButtonEvent(InputEvent: JavascriptInputEventState): boolean;
	static IsCtrlButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsLeftMouseButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsMiddleMouseButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsMouseButtonEvent(InputEvent: JavascriptInputEventState): boolean;
	static IsRightMouseButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsShiftButtonEvent(InputEvent: JavascriptInputEventState): boolean;
	static IsShiftButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsSpaceBarPressed(InputEvent: JavascriptInputEventState): boolean;
}

declare type EJavascriptWidgetMode = 'WM_Translate' | 'WM_TranslateRotateZ' | 'WM_2D' | 'WM_Rotate' | 'WM_Scale' | 'WM_Max' | 'WM_None';
declare var EJavascriptWidgetMode : { WM_Translate:'WM_Translate',WM_TranslateRotateZ:'WM_TranslateRotateZ',WM_2D:'WM_2D',WM_Rotate:'WM_Rotate',WM_Scale:'WM_Scale',WM_Max:'WM_Max',WM_None:'WM_None', };
declare class JavascriptEditorViewport extends PanelWidget { 
	OnClick: UnrealEngineDelegate<(ViewportClick: JavascriptViewportClick, HitProxy: JavascriptHitProxy, Instance: JavascriptEditorViewport) => void>;
	OnTrackingStarted: UnrealEngineDelegate<(InputState: JavascriptInputEventState, bIsDraggingWidget: boolean, bNudge: boolean, Instance: JavascriptEditorViewport) => void>;
	OnTrackingStopped: UnrealEngineDelegate<(Instance: JavascriptEditorViewport) => void>;
	OnInputWidgetDelta: UnrealEngineDelegate<(Drag: Vector, Rot: Rotator, Scale: Vector, Instance: JavascriptEditorViewport) => boolean>;
	OnInputKey: UnrealEngineDelegate<(ControllerId: number, Key: Key, Event: EInputEvent, Instance: JavascriptEditorViewport) => boolean>;
	OnInputAxis: UnrealEngineDelegate<(ControllerId: number, Key: Key, Delta: number, DeltaTime: number, Instance: JavascriptEditorViewport) => boolean>;
	OnMouseEnter: UnrealEngineDelegate<(X: number, Y: number, Instance: JavascriptEditorViewport) => boolean>;
	OnMouseMove: UnrealEngineDelegate<(X: number, Y: number, Instance: JavascriptEditorViewport) => boolean>;
	OnMouseLeave: UnrealEngineDelegate<(Instance: JavascriptEditorViewport) => boolean>;
	OnDraw: UnrealEngineDelegate<(PDI: JavascriptPDI, Instance: JavascriptEditorViewport) => void>;
	OnDrawCanvas: UnrealEngineDelegate<(Canvas: Canvas, Instance: JavascriptEditorViewport) => void>;
	OnGetWidgetLocation: UnrealEngineDelegate<(Instance: JavascriptEditorViewport) => Vector>;
	OnGetWidgetRotation: UnrealEngineDelegate<(Instance: JavascriptEditorViewport) => Rotator>;
	OnGetWidgetMode: UnrealEngineDelegate<(Instance: JavascriptEditorViewport) => EJavascriptWidgetMode>;
	static Load(ResourceName: string): JavascriptEditorViewport;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorViewport;
	static GetDefaultObject(): JavascriptEditorViewport;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorViewport;
	SetWidgetMode(WidgetMode: EJavascriptWidgetMode): void;
	SetViewRotation(ViewRotation: Rotator): void;
	SetViewportType(InViewportType: ELevelViewportType): void;
	SetViewMode(InViewModeIndex: EViewModeIndex): void;
	SetViewLocation(ViewLocation: Vector): void;
	SetViewFOV(InViewFOV: number): void;
	SetSkyBrightness(SkyBrightness: number): void;
	SetSimulatePhysics(bShouldSimulatePhysics: boolean): void;
	SetProfileIndex(InProfileIndex: number): void;
	SetLightLocation(InLightPos: Vector): void;
	SetLightDirection(InLightDir: Rotator): void;
	SetLightColor(LightColor: Color): void;
	SetLightBrightness(LightBrightness: number): void;
	SetFloorOffset(InFloorOffset: number): void;
	SetEngineShowFlags(In: string): boolean;
	SetCameraSpeedSetting(SpeedSetting: number): void;
	SetBackgroundColor(BackgroundColor: LinearColor): void;
	RemoveRealtimeOverride(SystemDisplayName: string): void;
	Redraw(): void;
	ProjectWorldToScreen(WorldPosition: Vector,OutScreenPosition?: Vector2D): {OutScreenPosition: Vector2D};
	OverridePostProcessSettings(PostProcessSettings: PostProcessSettings,Weight: number): void;
	GetWidgetMode(): EJavascriptWidgetMode;
	GetViewRotation(): Rotator;
	GetViewportWorld(): World;
	GetViewLocation(): Vector;
	GetViewFOV(): number;
	GetSkyComponent(): StaticMeshComponent;
	GetFloorMeshComponent(): StaticMeshComponent;
	GetEngineShowFlags(): string;
	GetDefaultSphereReflectionComponent(): SphereReflectionCaptureComponent;
	GetDefaultSkySphereComponent(): StaticMeshComponent;
	GetDefaultSkyLightComponent(): SkyLightComponent;
	GetDefaultPostProcessComponent(): PostProcessComponent;
	GetDefaultInstancedSkyMaterial(): MaterialInstanceConstant;
	GetDefaultDirectionalLightComponent(): DirectionalLightComponent;
	GetDefaultAssetViewerSettings(): AssetViewerSettings;
	GetCurrentProfileIndex(): number;
	GetCameraSpeedSetting(): number;
	DeprojectScreenToWorld(ScreenPosition: Vector2D,OutRayOrigin?: Vector,OutRayDirection?: Vector): {OutRayOrigin: Vector, OutRayDirection: Vector};
	AddRealtimeOverride(bInRealtime: boolean,SystemDisplayName: string): void;
	static C(Other: UObject | any): JavascriptEditorViewport;
}

declare class JavascriptEdViewport { 
	clone() : JavascriptEdViewport;
	static C(Other: UObject | any): JavascriptEdViewport;
	GetHitProxy(): JavascriptHitProxy;
	static GetHitProxy(Viewport: JavascriptEdViewport): JavascriptHitProxy;
}

declare class JavascriptEditorModeTools { 
	clone() : JavascriptEditorModeTools;
	static C(Other: UObject | any): JavascriptEditorModeTools;
	ActivateDefaultMode(): {Tools: JavascriptEditorModeTools};
	ActivateMode(InID?: string,bToggle?: boolean): {Tools: JavascriptEditorModeTools};
	DeactivateAllModes(): {Tools: JavascriptEditorModeTools};
	DeactivateMode(InID?: string): {Tools: JavascriptEditorModeTools};
	DestroyMode(InID?: string): {Tools: JavascriptEditorModeTools};
	EndTracking(Viewport: JavascriptEdViewport): boolean;
	EnsureNotInMode(ModeId?: string,ErrorMsg?: string,bNotifyUser?: boolean): {Tools: JavascriptEditorModeTools, $: boolean};
	IsDefaultModeActive(): {Tools: JavascriptEditorModeTools, $: boolean};
	IsModeActive(InID?: string): {Tools: JavascriptEditorModeTools, $: boolean};
	IsTracking(): boolean;
	SetDefaultMode(DefaultID?: string): {Tools: JavascriptEditorModeTools};
	StartTracking(Viewport: JavascriptEdViewport): boolean;
	static ActivateDefaultMode(Tools?: JavascriptEditorModeTools): {Tools: JavascriptEditorModeTools};
	static ActivateMode(Tools?: JavascriptEditorModeTools,InID?: string,bToggle?: boolean): {Tools: JavascriptEditorModeTools};
	static DeactivateAllModes(Tools?: JavascriptEditorModeTools): {Tools: JavascriptEditorModeTools};
	static DeactivateMode(Tools?: JavascriptEditorModeTools,InID?: string): {Tools: JavascriptEditorModeTools};
	static DestroyMode(Tools?: JavascriptEditorModeTools,InID?: string): {Tools: JavascriptEditorModeTools};
	static EndTracking(Tools: JavascriptEditorModeTools,Viewport: JavascriptEdViewport): boolean;
	static EnsureNotInMode(Tools?: JavascriptEditorModeTools,ModeId?: string,ErrorMsg?: string,bNotifyUser?: boolean): {Tools: JavascriptEditorModeTools, $: boolean};
	static IsDefaultModeActive(Tools?: JavascriptEditorModeTools): {Tools: JavascriptEditorModeTools, $: boolean};
	static IsModeActive(Tools?: JavascriptEditorModeTools,InID?: string): {Tools: JavascriptEditorModeTools, $: boolean};
	static IsTracking(Tools: JavascriptEditorModeTools): boolean;
	static SetDefaultMode(Tools?: JavascriptEditorModeTools,DefaultID?: string): {Tools: JavascriptEditorModeTools};
	static StartTracking(Tools: JavascriptEditorModeTools,Viewport: JavascriptEdViewport): boolean;
	static GetLevelEditorModeTools(): JavascriptEditorModeTools;
}

declare class JavascriptEditorMode { 
	clone() : JavascriptEditorMode;
	static C(Other: UObject | any): JavascriptEditorMode;
	GetCurrentWidgetAxis(): number;
	GetModeManager(): JavascriptEditorModeTools;
	SelectNone(): void;
	SetCurrentWidgetAxis(InAxis: number): void;
	static GetCurrentWidgetAxis(Mode: JavascriptEditorMode): number;
	static GetModeManager(Mode: JavascriptEditorMode): JavascriptEditorModeTools;
	static SelectNone(Mode: JavascriptEditorMode): void;
	static SetCurrentWidgetAxis(Mode: JavascriptEditorMode,InAxis: number): void;
}

declare type EJavascriptEditAction = 'Skip' | 'Process' | 'Halt' | 'EJavascriptEditAction_MAX';
declare var EJavascriptEditAction : { Skip:'Skip',Process:'Process',Halt:'Halt',EJavascriptEditAction_MAX:'EJavascriptEditAction_MAX', };
declare class JavascriptEdMode extends UObject { 
	OnGetWidgetLocation: UnrealEngineDelegate<(Instance: JavascriptEditorMode) => Vector>;
	OnSelect: UnrealEngineDelegate<(Actor: Actor, bSelected: boolean, Instance: JavascriptEditorMode) => boolean>;
	OnDraw: UnrealEngineDelegate<(PDI: JavascriptPDI, Instance: JavascriptEditorMode) => void>;
	OnDrawHUD: UnrealEngineDelegate<(Canvas: Canvas, Instance: JavascriptEditorMode) => void>;
	IsSelectionAllowed: UnrealEngineDelegate<(Actor: Actor, bSelected: boolean, Instance: JavascriptEditorMode) => boolean>;
	OnClick: UnrealEngineDelegate<(ViewportClick: JavascriptViewportClick, HitProxy: JavascriptHitProxy, Instance: JavascriptEditorMode) => boolean>;
	OnQuery: UnrealEngineDelegate<(Request: string, Instance: JavascriptEditorMode) => boolean>;
	OnStartTracking: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, Instance: JavascriptEditorMode) => boolean>;
	OnEndTracking: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, Instance: JavascriptEditorMode) => boolean>;
	OnInputAxis: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, ControllerId: number, Key: Key, Delta: number, DeltaTime: number, Instance: JavascriptEditorMode) => boolean>;
	OnInputKey: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, Key: Key, Event: EInputEvent, Instance: JavascriptEditorMode) => boolean>;
	OnInputDelta: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, Drag: Vector, Rot: Rotator, Scale: Vector, Instance: JavascriptEditorMode) => boolean>;
	OnCapturedMouseMove: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, X: number, Y: number, Instance: JavascriptEditorMode) => boolean>;
	OnMouseEnter: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, X: number, Y: number, Instance: JavascriptEditorMode) => boolean>;
	OnMouseLeave: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, Instance: JavascriptEditorMode) => boolean>;
	OnMouseMove: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, X: number, Y: number, Instance: JavascriptEditorMode) => boolean>;
	OnLostFocus: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, Instance: JavascriptEditorMode) => boolean>;
	OnReceivedFocus: UnrealEngineDelegate<(Viewport: JavascriptEdViewport, Instance: JavascriptEditorMode) => boolean>;
	OnSelectionChanged: UnrealEngineDelegate<(Tools: JavascriptEditorModeTools, Item: UObject) => void>;
	OnGetContent: UnrealEngineDelegate<() => Widget>;
	OnProcess: UnrealEngineDelegate<(Request: string, Instance: JavascriptEditorMode) => boolean>;
	OnGetAction: UnrealEngineDelegate<(Request: string, Instance: JavascriptEditorMode) => EJavascriptEditAction>;
	OnUsesToolkits: UnrealEngineDelegate<() => boolean>;
	OnIsCompatibleWith: UnrealEngineDelegate<(bIsCompatibleWith: string) => boolean>;
	OnActorMoved: UnrealEngineDelegate<(Instance: JavascriptEditorMode) => void>;
	OnActorsDuplicated: UnrealEngineDelegate<(PreDuplicateSelection: Actor[], PostDuplicateSelection: Actor[], bOffsetLocations: boolean, Instance: JavascriptEditorMode) => void>;
	OnActorSelectionChanged: UnrealEngineDelegate<(Instance: JavascriptEditorMode) => void>;
	OnActorPropChanged: UnrealEngineDelegate<(Instance: JavascriptEditorMode) => void>;
	OnMapChanged: UnrealEngineDelegate<(Instance: JavascriptEditorMode) => void>;
	ModeId: string;
	SlateIcon: JavascriptSlateIcon;
	ModeName: string;
	bVisible: boolean;
	PriorityOrder: number;
	static Load(ResourceName: string): JavascriptEdMode;
	static Find(Outer: UObject, ResourceName: string): JavascriptEdMode;
	static GetDefaultObject(): JavascriptEdMode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEdMode;
	Unregister(): void;
	Register(): void;
	static C(Other: UObject | any): JavascriptEdMode;
}

declare class JavascriptEdModeLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): JavascriptEdModeLibrary;
	static Find(Outer: UObject, ResourceName: string): JavascriptEdModeLibrary;
	static GetDefaultObject(): JavascriptEdModeLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEdModeLibrary;
	static StartTracking(Tools: JavascriptEditorModeTools,Viewport: JavascriptEdViewport): boolean;
	static SetDefaultMode(Tools?: JavascriptEditorModeTools,DefaultID?: string): {Tools: JavascriptEditorModeTools};
	static SetCurrentWidgetAxis(Mode: JavascriptEditorMode,InAxis: number): void;
	static SelectNone(Mode: JavascriptEditorMode): void;
	static IsTracking(Tools: JavascriptEditorModeTools): boolean;
	static IsModeActive(Tools?: JavascriptEditorModeTools,InID?: string): {Tools: JavascriptEditorModeTools, $: boolean};
	static IsDefaultModeActive(Tools?: JavascriptEditorModeTools): {Tools: JavascriptEditorModeTools, $: boolean};
	static GetModeManager(Mode: JavascriptEditorMode): JavascriptEditorModeTools;
	static GetLevelEditorModeTools(): JavascriptEditorModeTools;
	static GetHitProxy(Viewport: JavascriptEdViewport): JavascriptHitProxy;
	static GetCurrentWidgetAxis(Mode: JavascriptEditorMode): number;
	static EnsureNotInMode(Tools?: JavascriptEditorModeTools,ModeId?: string,ErrorMsg?: string,bNotifyUser?: boolean): {Tools: JavascriptEditorModeTools, $: boolean};
	static EndTracking(Tools: JavascriptEditorModeTools,Viewport: JavascriptEdViewport): boolean;
	static DestroyMode(Tools?: JavascriptEditorModeTools,InID?: string): {Tools: JavascriptEditorModeTools};
	static DeactivateMode(Tools?: JavascriptEditorModeTools,InID?: string): {Tools: JavascriptEditorModeTools};
	static DeactivateAllModes(Tools?: JavascriptEditorModeTools): {Tools: JavascriptEditorModeTools};
	static ActivateMode(Tools?: JavascriptEditorModeTools,InID?: string,bToggle?: boolean): {Tools: JavascriptEditorModeTools};
	static ActivateDefaultMode(Tools?: JavascriptEditorModeTools): {Tools: JavascriptEditorModeTools};
	static C(Other: UObject | any): JavascriptEdModeLibrary;
}

declare class JavascriptInputEventStateLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): JavascriptInputEventStateLibrary;
	static Find(Outer: UObject, ResourceName: string): JavascriptInputEventStateLibrary;
	static GetDefaultObject(): JavascriptInputEventStateLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptInputEventStateLibrary;
	static IsSpaceBarPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsShiftButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsShiftButtonEvent(InputEvent: JavascriptInputEventState): boolean;
	static IsRightMouseButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsMouseButtonEvent(InputEvent: JavascriptInputEventState): boolean;
	static IsMiddleMouseButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsLeftMouseButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsCtrlButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsCtrlButtonEvent(InputEvent: JavascriptInputEventState): boolean;
	static IsButtonPressed(InputEvent: JavascriptInputEventState,InKey: Key): boolean;
	static IsAnyMouseButtonDown(InputEvent: JavascriptInputEventState): boolean;
	static IsAltButtonPressed(InputEvent: JavascriptInputEventState): boolean;
	static IsAltButtonEvent(InputEvent: JavascriptInputEventState): boolean;
	static GetKey(InputEvent: JavascriptInputEventState): Key;
	static GetInputEvent(InputEvent: JavascriptInputEventState): EInputEvent;
	static C(Other: UObject | any): JavascriptInputEventStateLibrary;
}

declare class JavascriptLogSubscriber extends UObject { 
	OnNewLogMessage: UnrealEngineMulticastDelegate<(Message: string, Type: string, Category: string) => void>;
	static Load(ResourceName: string): JavascriptLogSubscriber;
	static Find(Outer: UObject, ResourceName: string): JavascriptLogSubscriber;
	static GetDefaultObject(): JavascriptLogSubscriber;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptLogSubscriber;
	static C(Other: UObject | any): JavascriptLogSubscriber;
}

declare class JavascriptMenuLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): JavascriptMenuLibrary;
	static Find(Outer: UObject, ResourceName: string): JavascriptMenuLibrary;
	static GetDefaultObject(): JavascriptMenuLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptMenuLibrary;
	static UI_COMMAND_Function(This: JavascriptBindingContext,Command: JavascriptUICommand,InTextSubNamespace: string): JavascriptUICommandInfo;
	static RemoveExtension(Extender: JavascriptExtender,Extension: JavascriptExtensionBase): void;
	static PushCommandList(Builder?: JavascriptMenuBuilder,List?: JavascriptUICommandList): {Builder: JavascriptMenuBuilder};
	static ProcessCommandBindings_PointerEvent(CommandList: JavascriptUICommandList,InMouseEvent: UPointerEvent): boolean;
	static ProcessCommandBindings_KeyEvent(CommandList: JavascriptUICommandList,InKeyEvent: KeyEvent): boolean;
	static PopCommandList(Builder?: JavascriptMenuBuilder): {Builder: JavascriptMenuBuilder};
	static NewBindingContext(InContextName: string,InContextDesc: string,InContextParent: string,InStyleSetName: string): JavascriptBindingContext;
	static GenericCommand(What: string): JavascriptUICommandInfo;
	static EndSection(Builder?: JavascriptMenuBuilder): {Builder: JavascriptMenuBuilder};
	static Destroy(Context: JavascriptBindingContext): void;
	static CreateUICommandList(): JavascriptUICommandList;
	static CreateToolbarBuilder(CommandList: JavascriptUICommandList,Orientation: EOrientation,UFunction: JavascriptFunction): void;
	static CreateMenuBuilder(CommandList: JavascriptUICommandList,bInShouldCloseWindowAfterMenuSelection: boolean,UFunction: JavascriptFunction): void;
	static CreateMenuBarBuilder(CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): void;
	static Combine(Extenders: JavascriptExtender[]): JavascriptExtender;
	static BeginSection(Builder?: JavascriptMenuBuilder,InExtensionHook?: string,MenuHeadingText?: string): {Builder: JavascriptMenuBuilder};
	static Apply(Extender: JavascriptExtender,ExtensionHook: string,HookPosition: EJavascriptExtensionHook,MenuBuilder?: JavascriptMenuBuilder): {MenuBuilder: JavascriptMenuBuilder};
	static AddWidget(Builder?: JavascriptMenuBuilder,Widget?: Widget,Label?: string,bNoIndent?: boolean,InTutorialHighlightName?: string,bSearchable?: boolean): {Builder: JavascriptMenuBuilder};
	static AddToolBarExtension(Extender: JavascriptExtender,ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	static AddToolBarButtonByContext(Builder?: JavascriptMenuBuilder,Context?: JavascriptToolbarButtonContext,EditingObject?: UObject): {Builder: JavascriptMenuBuilder};
	static AddToolBarButton(Builder?: JavascriptMenuBuilder,CommandInfo?: JavascriptUICommandInfo): {Builder: JavascriptMenuBuilder};
	static AddSubMenu(Builder?: JavascriptMenuBuilder,Label?: string,Tooltip?: string,bInOpenSubMenuOnClick?: boolean,UFunction?: JavascriptFunction): {Builder: JavascriptMenuBuilder};
	static AddSeparator(Builder?: JavascriptMenuBuilder): {Builder: JavascriptMenuBuilder};
	static AddPullDownMenu(MenuBuilder?: JavascriptMenuBuilder,InMenuLabel?: string,InToolTip?: string,InPullDownMenu?: JavascriptFunction,InExtensionHook?: string,InTutorialHighlightName?: string): {MenuBuilder: JavascriptMenuBuilder};
	static AddMenuExtension(Extender: JavascriptExtender,ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	static AddMenuEntry(Builder?: JavascriptMenuBuilder,UObject?: JavascriptMenuContext): {Builder: JavascriptMenuBuilder};
	static AddMenuByCommands(Builder?: JavascriptMenuBuilder,UICommands?: JavascriptUICommands): {Builder: JavascriptMenuBuilder};
	static AddMenubarExtension(Extender: JavascriptExtender,ExtensionHook: string,HookPosition: EJavascriptExtensionHook,CommandList: JavascriptUICommandList,UFunction: JavascriptFunction): JavascriptExtensionBase;
	static AddComboButton(Builder?: JavascriptMenuBuilder,UObject?: JavascriptComboButtonContext,EditingObject?: UObject): {Builder: JavascriptMenuBuilder};
	static C(Other: UObject | any): JavascriptMenuLibrary;
}

declare class JavascriptMultiBox extends Widget { 
	OnHook: UnrealEngineDelegate<(ID: string, Self: JavascriptMultiBox, CurrentBuilder: JavascriptMenuBuilder) => void>;
	static Load(ResourceName: string): JavascriptMultiBox;
	static Find(Outer: UObject, ResourceName: string): JavascriptMultiBox;
	static GetDefaultObject(): JavascriptMultiBox;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptMultiBox;
	static Bind(Builder: JavascriptMenuBuilder): void;
	AddSubMenu(Builder?: JavascriptMenuBuilder,ID?: string,Label?: string,Tooltip?: string,bInOpenSubMenuOnClick?: boolean): {Builder: JavascriptMenuBuilder};
	AddPullDownMenu(Builder?: JavascriptMenuBuilder,ID?: string,Label?: string,Tooltip?: string): {Builder: JavascriptMenuBuilder};
	static C(Other: UObject | any): JavascriptMultiBox;
}

declare type EJSCheckBoxState = 'Unchecked' | 'Checked' | 'Undetermined' | 'EJSCheckBoxState_MAX';
declare var EJSCheckBoxState : { Unchecked:'Unchecked',Checked:'Checked',Undetermined:'Undetermined',EJSCheckBoxState_MAX:'EJSCheckBoxState_MAX', };
declare class JavascriptNotification extends UObject { 
	text: string;
	bUseImage: boolean;
	UImage: SlateBrush;
	FadeInDuration: number;
	FadeOutDuration: number;
	ExpireDuration: number;
	bUseThrobber: boolean;
	bUseSuccessFailIcons: boolean;
	bUseLargeFont: boolean;
	bFireAndForget: boolean;
	CheckBoxState: EJSCheckBoxState;
	CheckBoxStateChanged: UnrealEngineDelegate<(State: ECheckBoxState) => void>;
	CheckBoxText: string;
	Hyperlink: UnrealEngineDelegate<() => void>;
	HyperlinkText: string;
	bAllowThrottleWhenFrameRateIsLow: boolean;
	static Load(ResourceName: string): JavascriptNotification;
	static Find(Outer: UObject, ResourceName: string): JavascriptNotification;
	static GetDefaultObject(): JavascriptNotification;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptNotification;
	Success(): void;
	SetText(InText: string): void;
	Reset(): void;
	Pending(): void;
	Fire(): void;
	Fail(): void;
	Fadeout(): void;
	static C(Other: UObject | any): JavascriptNotification;
}

declare type EPropertyAccessResult = 'MultipleValues' | 'Fail' | 'Success' | 'EPropertyAccessResult_MAX';
declare var EPropertyAccessResult : { MultipleValues:'MultipleValues',Fail:'Fail',Success:'Success',EPropertyAccessResult_MAX:'EPropertyAccessResult_MAX', };
declare class JavascriptPropertyHandle { 
	clone() : JavascriptPropertyHandle;
	static C(Other: UObject | any): JavascriptPropertyHandle;
	CreatePropertyNameWidget(NameOverride: string,ToolTipOverride: string,bDisplayResetToDefault: boolean,bHideText: boolean,bHideThumbnail: boolean): JavascriptSlateWidget;
	CreatePropertyValueWidget(bHideDefaultPropertyButtons: boolean): JavascriptSlateWidget;
	GeneratePathToProperty(): string;
	GetChildHandle(Name: string): JavascriptPropertyHandle;
	GetIndexInArray(): number;
	GetJavascriptRefValue(OutValue?: JavascriptRef): {OutValue: JavascriptRef, $: EPropertyAccessResult};
	GetKeyHandle(): JavascriptPropertyHandle;
	GetMetaData(Key: string): string;
	GetObjectValue(OutValue?: UObject): {OutValue: UObject, $: EPropertyAccessResult};
	GetOuterObjects(): UObject[];
	GetParentHandle(): JavascriptPropertyHandle;
	GetProperty(): any;
	GetValueAsFormattedString(OutValue?: string): {OutValue: string, $: EPropertyAccessResult};
	IsArrayProperty(): boolean;
	IsArrayPropertyWithValueType(): boolean;
	IsEditConst(): boolean;
	IsValidHandle(): boolean;
	SetJavascriptRefValue(InValue: JavascriptRef): EPropertyAccessResult;
	SetObjectValue(InValue: UObject): EPropertyAccessResult;
	SetOnPropertyValueChanged(Custom: JavascriptPropertyCustomization): void;
	SetValueFromFormattedString(InValue: string): EPropertyAccessResult;
	static CreatePropertyNameWidget(Handle: JavascriptPropertyHandle,NameOverride: string,ToolTipOverride: string,bDisplayResetToDefault: boolean,bHideText: boolean,bHideThumbnail: boolean): JavascriptSlateWidget;
	static CreatePropertyValueWidget(Handle: JavascriptPropertyHandle,bHideDefaultPropertyButtons: boolean): JavascriptSlateWidget;
	static GeneratePathToProperty(Handle: JavascriptPropertyHandle): string;
	static GetChildHandle(Parent: JavascriptPropertyHandle,Name: string): JavascriptPropertyHandle;
	static GetIndexInArray(Handle: JavascriptPropertyHandle): number;
	static GetJavascriptRefValue(Handle: JavascriptPropertyHandle,OutValue?: JavascriptRef): {OutValue: JavascriptRef, $: EPropertyAccessResult};
	static GetKeyHandle(Handle: JavascriptPropertyHandle): JavascriptPropertyHandle;
	static GetMetaData(Handle: JavascriptPropertyHandle,Key: string): string;
	static GetObjectValue(Handle: JavascriptPropertyHandle,OutValue?: UObject): {OutValue: UObject, $: EPropertyAccessResult};
	static GetOuterObjects(Handle: JavascriptPropertyHandle): UObject[];
	static GetParentHandle(Handle: JavascriptPropertyHandle): JavascriptPropertyHandle;
	static GetProperty(Handle: JavascriptPropertyHandle): any;
	static GetValueAsFormattedString(Handle: JavascriptPropertyHandle,OutValue?: string): {OutValue: string, $: EPropertyAccessResult};
	static IsArrayProperty(Handle: JavascriptPropertyHandle): boolean;
	static IsArrayPropertyWithValueType(Handle: JavascriptPropertyHandle): boolean;
	static IsEditConst(Handle: JavascriptPropertyHandle): boolean;
	static IsValidHandle(Handle: JavascriptPropertyHandle): boolean;
	static SetJavascriptRefValue(Handle: JavascriptPropertyHandle,InValue: JavascriptRef): EPropertyAccessResult;
	static SetObjectValue(Handle: JavascriptPropertyHandle,InValue: UObject): EPropertyAccessResult;
	static SetOnPropertyValueChanged(Handle: JavascriptPropertyHandle,Custom: JavascriptPropertyCustomization): void;
	static SetValueFromFormattedString(Handle: JavascriptPropertyHandle,InValue: string): EPropertyAccessResult;
}

declare class JavascriptDetailWidgetDecl { 
	clone() : JavascriptDetailWidgetDecl;
	static C(Other: UObject | any): JavascriptDetailWidgetDecl;
	SetContent(Widget: JavascriptSlateWidget): void;
	SetHAlign(InAlignment: EHorizontalAlignment): void;
	SetMaxDesiredWidth(MaxWidth: number): void;
	SetMinDesiredWidth(MinWidth: number): void;
	SetVAlign(InAlignment: EVerticalAlignment): void;
	static SetContent(Decl: JavascriptDetailWidgetDecl,Widget: JavascriptSlateWidget): void;
	static SetHAlign(Decl: JavascriptDetailWidgetDecl,InAlignment: EHorizontalAlignment): void;
	static SetMaxDesiredWidth(Decl: JavascriptDetailWidgetDecl,MaxWidth: number): void;
	static SetMinDesiredWidth(Decl: JavascriptDetailWidgetDecl,MinWidth: number): void;
	static SetVAlign(Decl: JavascriptDetailWidgetDecl,InAlignment: EVerticalAlignment): void;
}

declare class JavascriptDetailWidgetRow { 
	clone() : JavascriptDetailWidgetRow;
	static C(Other: UObject | any): JavascriptDetailWidgetRow;
	NameContent(): JavascriptDetailWidgetDecl;
	SetFilterString(InFilterString: string): void;
	ValueContent(): JavascriptDetailWidgetDecl;
	WholeRowContent(): JavascriptDetailWidgetDecl;
	static NameContent(Row: JavascriptDetailWidgetRow): JavascriptDetailWidgetDecl;
	static SetFilterString(Row: JavascriptDetailWidgetRow,InFilterString: string): void;
	static ValueContent(Row: JavascriptDetailWidgetRow): JavascriptDetailWidgetDecl;
	static WholeRowContent(Row: JavascriptDetailWidgetRow): JavascriptDetailWidgetDecl;
}

declare class JavascriptPropertyTypeCustomizationUtils { 
	clone() : JavascriptPropertyTypeCustomizationUtils;
	static C(Other: UObject | any): JavascriptPropertyTypeCustomizationUtils;
	RequestRefresh(bForce: boolean): void;
	static RequestRefresh(CustomizationUtils: JavascriptPropertyTypeCustomizationUtils,bForce: boolean): void;
}

declare class JavascriptSimpleGetBoolDelegateWrapper extends UObject { 
	delegate: UnrealEngineDelegate<() => boolean>;
	static Load(ResourceName: string): JavascriptSimpleGetBoolDelegateWrapper;
	static Find(Outer: UObject, ResourceName: string): JavascriptSimpleGetBoolDelegateWrapper;
	static GetDefaultObject(): JavascriptSimpleGetBoolDelegateWrapper;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptSimpleGetBoolDelegateWrapper;
	static C(Other: UObject | any): JavascriptSimpleGetBoolDelegateWrapper;
}

declare class JavascriptDetailPropertyRow { 
	clone() : JavascriptDetailPropertyRow;
	static C(Other: UObject | any): JavascriptDetailPropertyRow;
	BindVisibility(Wrapper: JavascriptSimpleGetBoolDelegateWrapper): void;
	CustomWidget(bShowChildren: boolean): JavascriptDetailWidgetRow;
	static BindVisibility(Row: JavascriptDetailPropertyRow,Wrapper: JavascriptSimpleGetBoolDelegateWrapper): void;
	static CustomWidget(Row: JavascriptDetailPropertyRow,bShowChildren: boolean): JavascriptDetailWidgetRow;
}

declare class JavascriptDetailChildrenBuilder { 
	clone() : JavascriptDetailChildrenBuilder;
	static C(Other: UObject | any): JavascriptDetailChildrenBuilder;
	AddChildContent(SearchString: string): JavascriptDetailWidgetRow;
	AddChildProperty(PropertyHandle: JavascriptPropertyHandle): JavascriptDetailPropertyRow;
	AddExternalObjectProperty(Objects?: UObject[],PropertyName?: string,UniqueIdName?: string,bAllowChildrenOverride?: boolean,bCreateCategoryNodesOverride?: boolean): {Objects: UObject[], $: JavascriptDetailPropertyRow};
	AddExternalObjects(Objects?: UObject[],UniqueIdName?: string): {Objects: UObject[], $: JavascriptDetailPropertyRow};
	GenerateStructValueWidget(StructPropertyHandle: JavascriptPropertyHandle): JavascriptSlateWidget;
	static AddChildContent(ChildBuilder: JavascriptDetailChildrenBuilder,SearchString: string): JavascriptDetailWidgetRow;
	static AddChildProperty(ChildBuilder: JavascriptDetailChildrenBuilder,PropertyHandle: JavascriptPropertyHandle): JavascriptDetailPropertyRow;
	static AddExternalObjectProperty(ChildBuilder: JavascriptDetailChildrenBuilder,Objects?: UObject[],PropertyName?: string,UniqueIdName?: string,bAllowChildrenOverride?: boolean,bCreateCategoryNodesOverride?: boolean): {Objects: UObject[], $: JavascriptDetailPropertyRow};
	static AddExternalObjects(ChildBuilder: JavascriptDetailChildrenBuilder,Objects?: UObject[],UniqueIdName?: string): {Objects: UObject[], $: JavascriptDetailPropertyRow};
	static GenerateStructValueWidget(ChildBuilder: JavascriptDetailChildrenBuilder,StructPropertyHandle: JavascriptPropertyHandle): JavascriptSlateWidget;
}

declare class JavascriptPropertyCustomization extends UObject { 
	PropertyTypeName: string;
	OnDestroy: UnrealEngineDelegate<(ID: number) => void>;
	OnCustomizeHeader: UnrealEngineDelegate<(Handle: JavascriptPropertyHandle, HeaderRow: JavascriptDetailWidgetRow, Utils: JavascriptPropertyTypeCustomizationUtils, ID: number) => void>;
	OnCustomizeChildren: UnrealEngineDelegate<(Handle: JavascriptPropertyHandle, ChildBuilder: JavascriptDetailChildrenBuilder, Utils: JavascriptPropertyTypeCustomizationUtils, ID: number) => void>;
	OnPropertyValueChanged: UnrealEngineMulticastDelegate<() => void>;
	static Load(ResourceName: string): JavascriptPropertyCustomization;
	static Find(Outer: UObject, ResourceName: string): JavascriptPropertyCustomization;
	static GetDefaultObject(): JavascriptPropertyCustomization;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptPropertyCustomization;
	Unregister(): void;
	Register(): void;
	static C(Other: UObject | any): JavascriptPropertyCustomization;
}

declare class JavascriptPropertyCustomizationLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): JavascriptPropertyCustomizationLibrary;
	static Find(Outer: UObject, ResourceName: string): JavascriptPropertyCustomizationLibrary;
	static GetDefaultObject(): JavascriptPropertyCustomizationLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptPropertyCustomizationLibrary;
	static WholeRowContent(Row: JavascriptDetailWidgetRow): JavascriptDetailWidgetDecl;
	static ValueContent(Row: JavascriptDetailWidgetRow): JavascriptDetailWidgetDecl;
	static SetValueFromFormattedString(Handle: JavascriptPropertyHandle,InValue: string): EPropertyAccessResult;
	static SetVAlign(Decl: JavascriptDetailWidgetDecl,InAlignment: EVerticalAlignment): void;
	static SetOnPropertyValueChanged(Handle: JavascriptPropertyHandle,Custom: JavascriptPropertyCustomization): void;
	static SetObjectValue(Handle: JavascriptPropertyHandle,InValue: UObject): EPropertyAccessResult;
	static SetMinDesiredWidth(Decl: JavascriptDetailWidgetDecl,MinWidth: number): void;
	static SetMaxDesiredWidth(Decl: JavascriptDetailWidgetDecl,MaxWidth: number): void;
	static SetJavascriptRefValue(Handle: JavascriptPropertyHandle,InValue: JavascriptRef): EPropertyAccessResult;
	static SetHAlign(Decl: JavascriptDetailWidgetDecl,InAlignment: EHorizontalAlignment): void;
	static SetFilterString(Row: JavascriptDetailWidgetRow,InFilterString: string): void;
	static SetContent(Decl: JavascriptDetailWidgetDecl,Widget: JavascriptSlateWidget): void;
	static RequestRefresh(CustomizationUtils: JavascriptPropertyTypeCustomizationUtils,bForce: boolean): void;
	static NameContent(Row: JavascriptDetailWidgetRow): JavascriptDetailWidgetDecl;
	static IsValidHandle(Handle: JavascriptPropertyHandle): boolean;
	static IsEditConst(Handle: JavascriptPropertyHandle): boolean;
	static IsArrayPropertyWithValueType(Handle: JavascriptPropertyHandle): boolean;
	static IsArrayProperty(Handle: JavascriptPropertyHandle): boolean;
	static GetValueAsFormattedString(Handle: JavascriptPropertyHandle,OutValue?: string): {OutValue: string, $: EPropertyAccessResult};
	static GetProperty(Handle: JavascriptPropertyHandle): any;
	static GetParentHandle(Handle: JavascriptPropertyHandle): JavascriptPropertyHandle;
	static GetOuterObjects(Handle: JavascriptPropertyHandle): UObject[];
	static GetObjectValue(Handle: JavascriptPropertyHandle,OutValue?: UObject): {OutValue: UObject, $: EPropertyAccessResult};
	static GetMetaData(Handle: JavascriptPropertyHandle,Key: string): string;
	static GetKeyHandle(Handle: JavascriptPropertyHandle): JavascriptPropertyHandle;
	static GetJavascriptRefValue(Handle: JavascriptPropertyHandle,OutValue?: JavascriptRef): {OutValue: JavascriptRef, $: EPropertyAccessResult};
	static GetIndexInArray(Handle: JavascriptPropertyHandle): number;
	static GetChildHandle(Parent: JavascriptPropertyHandle,Name: string): JavascriptPropertyHandle;
	static GenerateStructValueWidget(ChildBuilder: JavascriptDetailChildrenBuilder,StructPropertyHandle: JavascriptPropertyHandle): JavascriptSlateWidget;
	static GeneratePathToProperty(Handle: JavascriptPropertyHandle): string;
	static CustomWidget(Row: JavascriptDetailPropertyRow,bShowChildren: boolean): JavascriptDetailWidgetRow;
	static CreatePropertyValueWidget(Handle: JavascriptPropertyHandle,bHideDefaultPropertyButtons: boolean): JavascriptSlateWidget;
	static CreatePropertyNameWidget(Handle: JavascriptPropertyHandle,NameOverride: string,ToolTipOverride: string,bDisplayResetToDefault: boolean,bHideText: boolean,bHideThumbnail: boolean): JavascriptSlateWidget;
	static BindVisibility(Row: JavascriptDetailPropertyRow,Wrapper: JavascriptSimpleGetBoolDelegateWrapper): void;
	static AddExternalObjects(ChildBuilder: JavascriptDetailChildrenBuilder,Objects?: UObject[],UniqueIdName?: string): {Objects: UObject[], $: JavascriptDetailPropertyRow};
	static AddExternalObjectProperty(ChildBuilder: JavascriptDetailChildrenBuilder,Objects?: UObject[],PropertyName?: string,UniqueIdName?: string,bAllowChildrenOverride?: boolean,bCreateCategoryNodesOverride?: boolean): {Objects: UObject[], $: JavascriptDetailPropertyRow};
	static AddChildProperty(ChildBuilder: JavascriptDetailChildrenBuilder,PropertyHandle: JavascriptPropertyHandle): JavascriptDetailPropertyRow;
	static AddChildContent(ChildBuilder: JavascriptDetailChildrenBuilder,SearchString: string): JavascriptDetailWidgetRow;
	static C(Other: UObject | any): JavascriptPropertyCustomizationLibrary;
}

declare type EPropertyEditorNameAreaSettings = 'HideNameArea' | 'ObjectsUseNameArea' | 'ActorsUseNameArea' | 'ComponentsAndActorsUseNameArea' | 'EPropertyEditorNameAreaSettings_MAX';
declare var EPropertyEditorNameAreaSettings : { HideNameArea:'HideNameArea',ObjectsUseNameArea:'ObjectsUseNameArea',ActorsUseNameArea:'ActorsUseNameArea',ComponentsAndActorsUseNameArea:'ComponentsAndActorsUseNameArea',EPropertyEditorNameAreaSettings_MAX:'EPropertyEditorNameAreaSettings_MAX', };
declare class PropertyEditor extends Widget { 
	OnChange: UnrealEngineMulticastDelegate<(PropertyName: string, MemberPropertyName: string) => void>;
	bUpdateFromSelection: boolean;
	bLockable: boolean;
	bAllowSearch: boolean;
	bHideSelectionTip: boolean;
	bReadOnly: boolean;
	bEnablePropertyPath: boolean;
	NameAreaSettings: EPropertyEditorNameAreaSettings;
	static Load(ResourceName: string): PropertyEditor;
	static Find(Outer: UObject, ResourceName: string): PropertyEditor;
	static GetDefaultObject(): PropertyEditor;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): PropertyEditor;
	SetObjects(Objects: UObject[],bForceRefresh: boolean,bOverrideLock: boolean): void;
	SetObject(UObject: UObject,bForceRefresh: boolean): void;
	IsPropertyVisible(PropertName: string,ParentPropertyName: string,PropertyPaths: string[]): boolean;
	IsPropertyReadOnly(PropertyName: string,ParentPropertyName: string,PropertyPaths: string[]): boolean;
	ForceRefresh(): void;
	Destruct(): void;
	Construct(): void;
	static C(Other: UObject | any): PropertyEditor;
}

declare class JavascriptPropertyTable extends Widget { 
	OnGenerateInvalidCellWidget: UnrealEngineDelegate<() => JavascriptSlateWidget>;
	bUseCustomColumns: boolean;
	static Load(ResourceName: string): JavascriptPropertyTable;
	static Find(Outer: UObject, ResourceName: string): JavascriptPropertyTable;
	static GetDefaultObject(): JavascriptPropertyTable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptPropertyTable;
	SetEditingObjects(InEditingObjects: UObject[]): void;
	GetSelectedTableObjects(): UObject[];
	GetEditingObjects(): UObject[];
	static C(Other: UObject | any): JavascriptPropertyTable;
}

declare class JavascriptRawMeshLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): JavascriptRawMeshLibrary;
	static Find(Outer: UObject, ResourceName: string): JavascriptRawMeshLibrary;
	static GetDefaultObject(): JavascriptRawMeshLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptRawMeshLibrary;
	static SetSectionInfo(StaticMesh: StaticMesh,LODIndex: number,SectionIndex: number,Info: MeshSectionInfo): void;
	static SaveRawMesh(StaticMesh: StaticMesh,SourceModelIndex: number,InMesh?: JavascriptRawMesh): {InMesh: JavascriptRawMesh};
	static LoadRawMesh(StaticMesh: StaticMesh,SourceModelIndex: number,OutMesh?: JavascriptRawMesh): {OutMesh: JavascriptRawMesh};
	static IsValidOrFixable(RawMesh: JavascriptRawMesh): boolean;
	static IsValid(RawMesh: JavascriptRawMesh): boolean;
	static GetWedgePosition(RawMesh: JavascriptRawMesh,WedgeIndex: number): Vector;
	static GetSectionInfo(StaticMesh: StaticMesh,LODIndex: number,SectionIndex: number): MeshSectionInfo;
	static Empty(RawMesh?: JavascriptRawMesh): {RawMesh: JavascriptRawMesh};
	static CompactMaterialIndices(RawMesh?: JavascriptRawMesh): {RawMesh: JavascriptRawMesh};
	static Build(StaticMesh: StaticMesh): void;
	static C(Other: UObject | any): JavascriptRawMeshLibrary;
}

declare class JavascriptScrubControlPanel extends Widget { 
	OnClick_Forward_Delegate: UnrealEngineMulticastDelegate<() => void>;
	OnClick_Forward_Step_Delegate: UnrealEngineMulticastDelegate<() => void>;
	OnClick_Forward_End_Delegate: UnrealEngineMulticastDelegate<() => void>;
	OnClick_Backward_Delegate: UnrealEngineMulticastDelegate<() => void>;
	OnClick_Backward_Step_Delegate: UnrealEngineMulticastDelegate<() => void>;
	OnClick_Backward_End_Delegate: UnrealEngineMulticastDelegate<() => void>;
	OnClick_ToggleLoop_Delegate: UnrealEngineMulticastDelegate<() => void>;
	SetPlaybackPosition_Delegate: UnrealEngineMulticastDelegate<() => void>;
	static Load(ResourceName: string): JavascriptScrubControlPanel;
	static Find(Outer: UObject, ResourceName: string): JavascriptScrubControlPanel;
	static GetDefaultObject(): JavascriptScrubControlPanel;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptScrubControlPanel;
	SetViewRange(NewMin: number,NewMax: number): void;
	SetSumFrames(NewSumFrames: number): void;
	SetPlaybackPosition(NewTime: number): void;
	SetLooping(NewbLooping: boolean): void;
	SetFramesPerSecond(NewFramesPerSecond: number): void;
	IsLooping(): boolean;
	GetViewRangeMin(): number;
	GetViewRangeMax(): number;
	GetTotalSequenceLength(): number;
	GetTotalFrameCount(): number;
	GetPlaybackPosition(): number;
	GetFramesPerSecond(): number;
	static C(Other: UObject | any): JavascriptScrubControlPanel;
}

declare class JavascriptWebBrowser extends Widget { 
	OnUrlChanged: UnrealEngineMulticastDelegate<(text: string) => void>;
	OnBeforePopup: UnrealEngineMulticastDelegate<(URL: string, Frame: string) => void>;
	bShowAddressBar: boolean;
	bShowControls: boolean;
	bSupportsThumbMouseButtonNavigation: boolean;
	static Load(ResourceName: string): JavascriptWebBrowser;
	static Find(Outer: UObject, ResourceName: string): JavascriptWebBrowser;
	static GetDefaultObject(): JavascriptWebBrowser;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptWebBrowser;
	LoadURL(NewURL: string): void;
	LoadString(Contents: string,DummyURL: string): void;
	GetUrl(): string;
	GetTitleText(): string;
	ExecuteJavascript(ScriptText: string): void;
	static C(Other: UObject | any): JavascriptWebBrowser;
}

declare class JavascriptPinParams { 
	ContainerType: EPinContainerType;
	bIsReference: boolean;
	bIsConst: boolean;
	index: number;
	clone() : JavascriptPinParams;
	static C(Other: UObject | any): JavascriptPinParams;
}

declare class JavascriptGraphEdNode extends EdGraphNode { 
	BackgroundColor: SlateColor;
	GraphNode: UObject;
	IsTitleOnly: boolean;
	IsCustomNode: boolean;
	WidgetFinalized: JavascriptFunction;
	Bidirectional: boolean;
	PriorityOrder: number;
	static Load(ResourceName: string): JavascriptGraphEdNode;
	static Find(Outer: UObject, ResourceName: string): JavascriptGraphEdNode;
	static GetDefaultObject(): JavascriptGraphEdNode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGraphEdNode;
	UpdateSlate(): void;
	SetVisible(bVisible: boolean): void;
	SetTitleSelectionMode(InTitleHeight: number): void;
	SetEnable(bEnable: boolean): void;
	ResetTitleSelectionMode(): void;
	RemovePinByName(PinName: string): boolean;
	RemovePin(Pin: JavascriptEdGraphPin): boolean;
	GetVisible(): boolean;
	GetNumOfPins(Direction: EEdGraphPinDirection): number;
	GetDesiredSize(): Vector2D;
	CreatePin(Dir: EEdGraphPinDirection,PinCategory: string,PinSubCategory: string,PinSubCategoryObject: UObject,PinName: string,PinToolTip: string,PinDisplayName: string,InPinParams: JavascriptPinParams): JavascriptEdGraphPin;
	static C(Other: UObject | any): JavascriptGraphEdNode;
	GetOwnerPanel(): JavascriptSlateWidget;
	static GetOwnerPanel(UNode: JavascriptGraphEdNode): JavascriptSlateWidget;
}

declare class JavascriptSlateEdNode { 
	clone() : JavascriptSlateEdNode;
	static C(Other: UObject | any): JavascriptSlateEdNode;
	AddPinToHoverSet(Pin: JavascriptEdGraphPin): void;
	RemovePinFromHoverSet(Pin: JavascriptEdGraphPin): void;
	static AddPinToHoverSet(InSlateEdNode: JavascriptSlateEdNode,Pin: JavascriptEdGraphPin): void;
	static RemovePinFromHoverSet(InSlateNode: JavascriptSlateEdNode,Pin: JavascriptEdGraphPin): void;
}

declare class JavascriptPerformSecondPassLayoutContainer { 
	PrevNode: EdGraphNode;
	NextNode: EdGraphNode;
	NodeIndex: number;
	MaxNodes: number;
	clone() : JavascriptPerformSecondPassLayoutContainer;
	static C(Other: UObject | any): JavascriptPerformSecondPassLayoutContainer;
}

declare class JavascriptConnectionParams { 
	WireColor: LinearColor;
	AssociatedPin1: JavascriptEdGraphPin;
	AssociatedPin2: JavascriptEdGraphPin;
	WireThickness: number;
	bDrawBubbles: boolean;
	bUserFlag1: boolean;
	bUserFlag2: boolean;
	StartDirection: EEdGraphPinDirection;
	EndDirection: EEdGraphPinDirection;
	clone() : JavascriptConnectionParams;
	static C(Other: UObject | any): JavascriptConnectionParams;
}

declare class JavascriptGraphConnectionDrawingPolicyContainer { 
	clone() : JavascriptGraphConnectionDrawingPolicyContainer;
	static C(Other: UObject | any): JavascriptGraphConnectionDrawingPolicyContainer;
	ApplyHoverDeemphasis(OutputPin: JavascriptEdGraphPin,InputPin: JavascriptEdGraphPin,Thickness: number,WireColor: LinearColor): void;
	DetermineWiringStyle(OutputPin: JavascriptEdGraphPin,InputPin: JavascriptEdGraphPin,Params?: JavascriptConnectionParams): {Params: JavascriptConnectionParams};
	DrawConnection(A: Vector2D,B: Vector2D,Params: JavascriptConnectionParams): void;
	DrawSplineWithArrow(StartAnchorPoint: Vector2D,EndAnchorPoint: Vector2D,Params: JavascriptConnectionParams): void;
	GetHorveredPinNum(): number;
	IsContainedHoveredPins(Pin: JavascriptEdGraphPin): boolean;
	MakeRotatedBox(ArrowDrawPos: Vector2D,AngleInRadians: number,WireColor: LinearColor): void;
	static ApplyHoverDeemphasis(Container: JavascriptGraphConnectionDrawingPolicyContainer,OutputPin: JavascriptEdGraphPin,InputPin: JavascriptEdGraphPin,Thickness: number,WireColor: LinearColor): void;
	static DetermineWiringStyle(Container: JavascriptGraphConnectionDrawingPolicyContainer,OutputPin: JavascriptEdGraphPin,InputPin: JavascriptEdGraphPin,Params?: JavascriptConnectionParams): {Params: JavascriptConnectionParams};
	static DrawConnection(Container: JavascriptGraphConnectionDrawingPolicyContainer,A: Vector2D,B: Vector2D,Params: JavascriptConnectionParams): void;
	static DrawSplineWithArrow(Container: JavascriptGraphConnectionDrawingPolicyContainer,StartAnchorPoint: Vector2D,EndAnchorPoint: Vector2D,Params: JavascriptConnectionParams): void;
	static GetHorveredPinNum(Container: JavascriptGraphConnectionDrawingPolicyContainer): number;
	static IsContainedHoveredPins(Container: JavascriptGraphConnectionDrawingPolicyContainer,Pin: JavascriptEdGraphPin): boolean;
	static MakeRotatedBox(Container: JavascriptGraphConnectionDrawingPolicyContainer,ArrowDrawPos: Vector2D,AngleInRadians: number,WireColor: LinearColor): void;
}

declare type EGraphSchemaGetStringQuery = 'Description' | 'Title' | 'EGraphSchemaGetStringQuery_MAX';
declare var EGraphSchemaGetStringQuery : { Description:'Description',Title:'Title',EGraphSchemaGetStringQuery_MAX:'EGraphSchemaGetStringQuery_MAX', };
declare class JavascriptGraphMenuBuilder extends JavascriptMenuBuilder { 
	Graph: EdGraph;
	GraphNode: EdGraphNode;
	GraphPin: JavascriptEdGraphPin;
	bIsDebugging: boolean;
	clone() : JavascriptGraphMenuBuilder;
	static C(Other: UObject | any): JavascriptGraphMenuBuilder;
}

declare type ECanCreateConnectionResponse = 'CONNECT_RESPONSE_MAKE' | 'CONNECT_RESPONSE_DISALLOW' | 'CONNECT_RESPONSE_BREAK_OTHERS_A' | 'CONNECT_RESPONSE_BREAK_OTHERS_B' | 'CONNECT_RESPONSE_BREAK_OTHERS_AB' | 'CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE' | 'CONNECT_RESPONSE_MAKE_WITH_PROMOTION' | 'CONNECT_RESPONSE_MAX';
declare var ECanCreateConnectionResponse : { CONNECT_RESPONSE_MAKE:'CONNECT_RESPONSE_MAKE',CONNECT_RESPONSE_DISALLOW:'CONNECT_RESPONSE_DISALLOW',CONNECT_RESPONSE_BREAK_OTHERS_A:'CONNECT_RESPONSE_BREAK_OTHERS_A',CONNECT_RESPONSE_BREAK_OTHERS_B:'CONNECT_RESPONSE_BREAK_OTHERS_B',CONNECT_RESPONSE_BREAK_OTHERS_AB:'CONNECT_RESPONSE_BREAK_OTHERS_AB',CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE:'CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE',CONNECT_RESPONSE_MAKE_WITH_PROMOTION:'CONNECT_RESPONSE_MAKE_WITH_PROMOTION',CONNECT_RESPONSE_MAX:'CONNECT_RESPONSE_MAX', };
declare class JavascriptPinConnectionResponse { 
	Message: string;
	Response: ECanCreateConnectionResponse;
	clone() : JavascriptPinConnectionResponse;
	static C(Other: UObject | any): JavascriptPinConnectionResponse;
}

declare class EdGraphSchemaAction { 
	MenuDescription: string;
	TooltipDescription: string;
	Category: string;
	Keywords: string;
	Grouping: number;
	SectionID: number;
	MenuDescriptionArray: string[];
	FullSearchTitlesArray: string[];
	FullSearchKeywordsArray: string[];
	FullSearchCategoryArray: string[];
	LocalizedMenuDescriptionArray: string[];
	LocalizedFullSearchTitlesArray: string[];
	LocalizedFullSearchKeywordsArray: string[];
	LocalizedFullSearchCategoryArray: string[];
	SearchText: string;
	clone() : EdGraphSchemaAction;
	static C(Other: UObject | any): EdGraphSchemaAction;
}

declare class PerformActionContext { 
	ParentGraph: EdGraph;
	FromPins: JavascriptEdGraphPin[];
	Location: Vector2D;
	bSelectNewNode: boolean;
	clone() : PerformActionContext;
	static C(Other: UObject | any): PerformActionContext;
}

declare class JavascriptArrangedWidget { 
	clone() : JavascriptArrangedWidget;
	static C(Other: UObject | any): JavascriptArrangedWidget;
}

declare class JavascriptPinWidget { 
	clone() : JavascriptPinWidget;
	static C(Other: UObject | any): JavascriptPinWidget;
}

declare class JavascriptDetermineLinkGeometryContainer { 
	clone() : JavascriptDetermineLinkGeometryContainer;
	static C(Other: UObject | any): JavascriptDetermineLinkGeometryContainer;
	FindPinGeometries(PinWidget: JavascriptPinWidget): JavascriptArrangedWidget;
	FindPinToPinWidgetMap(Pin: JavascriptEdGraphPin): JavascriptPinWidget;
	GetArrangedNodes(UNode: EdGraphNode): JavascriptArrangedWidget;
	GetOutputPinWidget(): JavascriptPinWidget;
	static FindPinGeometries(Container: JavascriptDetermineLinkGeometryContainer,PinWidget: JavascriptPinWidget): JavascriptArrangedWidget;
	static FindPinToPinWidgetMap(Container: JavascriptDetermineLinkGeometryContainer,Pin: JavascriptEdGraphPin): JavascriptPinWidget;
	static GetArrangedNodes(Container: JavascriptDetermineLinkGeometryContainer,UNode: EdGraphNode): JavascriptArrangedWidget;
	static GetOutputPinWidget(Container: JavascriptDetermineLinkGeometryContainer): JavascriptPinWidget;
}

declare class JavascriptGraphAssetGraphSchema extends EdGraphSchema { 
	OnGetPinColor: UnrealEngineDelegate<(bHovered: boolean, Pin: JavascriptEdGraphPin) => SlateColor>;
	OnGetPinTextColor: UnrealEngineDelegate<(bHovered: boolean, Pin: JavascriptEdGraphPin) => SlateColor>;
	OnGetDefaultValueVisibility: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => boolean>;
	OnGetSlateBrushName: UnrealEngineDelegate<(bHovered: boolean, Pin: JavascriptEdGraphPin) => string>;
	OnPinConnectionListChanged: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => void>;
	OnTryCreateConnection: UnrealEngineDelegate<(PinA: JavascriptEdGraphPin, PinB: JavascriptEdGraphPin) => void>;
	OnMouseEnter: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode, SlateEdNode: JavascriptSlateEdNode, UPointerEvent: UPointerEvent) => void>;
	OnMouseLeave: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode, SlateEdNode: JavascriptSlateEdNode, UPointerEvent: UPointerEvent) => void>;
	OnMouseMove: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode, Delta: Vector2D, bUserIsDragging: boolean, MouseZone: number, UPointerEvent: UPointerEvent) => boolean>;
	OnMouseButtonDown: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode, MyGeometry: Geometry, UPointerEvent: UPointerEvent) => boolean>;
	OnMouseButtonUp: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode, MyGeometry: Geometry, UPointerEvent: UPointerEvent) => boolean>;
	OnPerformSecondPassLayout: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => JavascriptPerformSecondPassLayoutContainer>;
	OnRequiresSecondPassLayout: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => boolean>;
	OnMoveTo: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode, NewPosition: Vector2D) => boolean>;
	OnTakeContentWidget: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode, OutLeftNodeBoxWidget: JavascriptSlateWidget, OutRightNodeBoxWidget: JavascriptSlateWidget) => JavascriptSlateWidget>;
	OnGetValueWidget: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => JavascriptSlateWidget>;
	OnGetActualPinWidget: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => JavascriptSlateWidget>;
	OnGetPinStatusIndicator: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => JavascriptSlateWidget>;
	OnDisableMakePins: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => boolean>;
	OnUsingDefaultPin: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => boolean>;
	OnGetPinLabelVisibility: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => boolean>;
	OnGetCustomPinBoxWidget: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => JavascriptSlateWidget>;
	OnUsingNodeWidgetMap: UnrealEngineDelegate<() => boolean>;
	OnDetermineWiringStyle: UnrealEngineDelegate<(A: JavascriptEdGraphPin, B: JavascriptEdGraphPin, Params: JavascriptConnectionParams, Container: JavascriptGraphConnectionDrawingPolicyContainer) => void>;
	OnComputeSplineTangent: UnrealEngineDelegate<(A: Vector2D, B: Vector2D) => Vector2D>;
	OnDrawSplineWithArrow: UnrealEngineDelegate<(A: Vector2D, B: Vector2D, Params: JavascriptConnectionParams, Container: JavascriptGraphConnectionDrawingPolicyContainer, ArrowRadius: Vector2D) => boolean>;
	OnDrawSplineWithArrow_Geom: UnrealEngineDelegate<(A: Geometry, B: Geometry, Params: JavascriptConnectionParams, Container: JavascriptGraphConnectionDrawingPolicyContainer) => boolean>;
	OnDrawPreviewConnector: UnrealEngineDelegate<(PinGeometry: Geometry, StartPoint: Vector2D, Endpoint: Vector2D, Pin: JavascriptEdGraphPin, Params: JavascriptConnectionParams, Container: JavascriptGraphConnectionDrawingPolicyContainer) => boolean>;
	OnTakeUserWidget: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => JavascriptSlateWidget>;
	OnTakeTitleAreaWidget: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => JavascriptSlateWidget>;
	OnTakeErrorReportingWidget: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => JavascriptSlateWidget>;
	OnGetString: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode, Query: EGraphSchemaGetStringQuery) => string>;
	OnBuildMenu: UnrealEngineDelegate<(Builder: JavascriptGraphMenuBuilder) => void>;
	OnAllocateDefaultPins: UnrealEngineDelegate<(UNode: JavascriptGraphEdNode) => void>;
	OnCreatePin: UnrealEngineDelegate<(Pin: JavascriptEdGraphPin) => JavascriptSlateWidget>;
	OnCanCreateConnection: UnrealEngineDelegate<(A: JavascriptEdGraphPin, B: JavascriptEdGraphPin) => JavascriptPinConnectionResponse>;
	OnPerformAction: UnrealEngineDelegate<(Action: EdGraphSchemaAction, Context: PerformActionContext) => EdGraphNode>;
	OnContextActions: UnrealEngineDelegate<(FromPin: JavascriptEdGraphPin) => EdGraphSchemaAction[]>;
	OnNodeConnectionListChanged: UnrealEngineDelegate<(UNode: JavascriptGraphEdNode) => void>;
	OnCreateAutomaticConversionNodeAndConnections: UnrealEngineDelegate<(A: JavascriptEdGraphPin, B: JavascriptEdGraphPin) => boolean>;
	OnDetermineLinkGeometry: UnrealEngineDelegate<(OutPin: JavascriptEdGraphPin, InputPin: JavascriptEdGraphPin, StartWidgetGeometry: JavascriptArrangedWidget, EndWidgetGeometry: JavascriptArrangedWidget, Container: JavascriptDetermineLinkGeometryContainer) => boolean>;
	OnIsNodeComment: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => boolean>;
	OnEndUserInteraction: UnrealEngineDelegate<(UNode: JavascriptGraphEdNode) => void>;
	OnCreateOutputSideAddButton: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => boolean>;
	OnAddPinByAddButton: UnrealEngineDelegate<(UNode: JavascriptGraphEdNode) => void>;
	OnShouldAlwaysPurgeOnModification: UnrealEngineDelegate<() => boolean>;
	OnDragEnter: UnrealEngineDelegate<(Target: JavascriptGraphEdNode, Capture: JavascriptGraphEdNode, MyGeometry: Geometry) => boolean>;
	OnDragLeave: UnrealEngineDelegate<(Instance: JavascriptGraphEdNode) => boolean>;
	OnDragOver: UnrealEngineDelegate<(Target: JavascriptGraphEdNode, Capture: JavascriptGraphEdNode, MyGeometry: Geometry) => boolean>;
	OnDrop: UnrealEngineDelegate<(Target: JavascriptGraphEdNode, Capture: JavascriptGraphEdNode, MyGeometry: Geometry) => boolean>;
	static Load(ResourceName: string): JavascriptGraphAssetGraphSchema;
	static Find(Outer: UObject, ResourceName: string): JavascriptGraphAssetGraphSchema;
	static GetDefaultObject(): JavascriptGraphAssetGraphSchema;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGraphAssetGraphSchema;
	BreakSinglePinLink(SourcePin: JavascriptEdGraphPin,TargetPin: JavascriptEdGraphPin): void;
	BreakPinLinks(TargetPin: JavascriptEdGraphPin,bSendsNodeNotifcation: boolean): void;
	BreakNodeLinks(TargetNode: EdGraphNode): void;
	static C(Other: UObject | any): JavascriptGraphAssetGraphSchema;
}

declare class JavascriptGraphEdCustomNodeWidget extends Widget { 
	EdNode: JavascriptGraphEdNode;
	static Load(ResourceName: string): JavascriptGraphEdCustomNodeWidget;
	static Find(Outer: UObject, ResourceName: string): JavascriptGraphEdCustomNodeWidget;
	static GetDefaultObject(): JavascriptGraphEdCustomNodeWidget;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGraphEdCustomNodeWidget;
	SetNode(InEdNode: JavascriptGraphEdNode): void;
	SetGraphPanel(InGraphPanel: JavascriptSlateWidget): void;
	static C(Other: UObject | any): JavascriptGraphEdCustomNodeWidget;
}

declare class JavascriptNodeCreator { 
	UNode: JavascriptGraphEdNode;
	clone() : JavascriptNodeCreator;
	static C(Other: UObject | any): JavascriptNodeCreator;
	Finalize(): {Creator: JavascriptNodeCreator};
	static Finalize(Creator?: JavascriptNodeCreator): {Creator: JavascriptNodeCreator};
}

declare class JavascriptGraphEdGraph extends EdGraph { 
	CustomNodes: JavascriptGraphEdNode[];
	static Load(ResourceName: string): JavascriptGraphEdGraph;
	static Find(Outer: UObject, ResourceName: string): JavascriptGraphEdGraph;
	static GetDefaultObject(): JavascriptGraphEdGraph;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGraphEdGraph;
	RebuildGenericGraph(): void;
	static C(Other: UObject | any): JavascriptGraphEdGraph;
	CustomNodeCreator(): JavascriptNodeCreator;
	NodeCreator(bSelectNewNode: boolean): JavascriptNodeCreator;
	static CustomNodeCreator(Graph: JavascriptGraphEdGraph): JavascriptNodeCreator;
	static NodeCreator(Graph: JavascriptGraphEdGraph,bSelectNewNode: boolean): JavascriptNodeCreator;
}

declare class JavascriptGraphEditorLibrary extends BlueprintFunctionLibrary { 
	static Load(ResourceName: string): JavascriptGraphEditorLibrary;
	static Find(Outer: UObject, ResourceName: string): JavascriptGraphEditorLibrary;
	static GetDefaultObject(): JavascriptGraphEditorLibrary;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGraphEditorLibrary;
	static TryConnection(Schema: EdGraphSchema,A: JavascriptEdGraphPin,B: JavascriptEdGraphPin): void;
	static SetPinType(Pin: JavascriptEdGraphPin,PinType: EdGraphPinType): void;
	static SetPinInfo(A: JavascriptEdGraphPin,InPinName: string,InPinToolTip: string): void;
	static SetPinHidden(A: JavascriptEdGraphPin,bHidden: boolean): void;
	static SetPinContainerType(A: JavascriptEdGraphPin,ContainerType: EJavascriptPinContainerType): void;
	static SetParentPin(A: JavascriptEdGraphPin,Parent: JavascriptEdGraphPin): void;
	static SetNodeMetaData(Schema: EdGraphSchema,UNode: EdGraphNode,KeyValue: string): boolean;
	static ResizeNode(UNode: EdGraphNode,NewSize: Vector2D): void;
	static RemovePinFromHoverSet(InSlateNode: JavascriptSlateEdNode,Pin: JavascriptEdGraphPin): void;
	static NodeCreator(Graph: JavascriptGraphEdGraph,bSelectNewNode: boolean): JavascriptNodeCreator;
	static MakeRotatedBox(Container: JavascriptGraphConnectionDrawingPolicyContainer,ArrowDrawPos: Vector2D,AngleInRadians: number,WireColor: LinearColor): void;
	static MakeLinkTo(A: JavascriptEdGraphPin,B: JavascriptEdGraphPin): void;
	static IsValid(A: JavascriptEdGraphPin): boolean;
	static IsPinHidden(A: JavascriptEdGraphPin): boolean;
	static IsContainedHoveredPins(Container: JavascriptGraphConnectionDrawingPolicyContainer,Pin: JavascriptEdGraphPin): boolean;
	static GetSubPins(A: JavascriptEdGraphPin): JavascriptEdGraphPin[];
	static GetPinType(A: JavascriptEdGraphPin): EdGraphPinType;
	static GetPins(UNode: EdGraphNode): JavascriptEdGraphPin[];
	static GetPinName(A: JavascriptEdGraphPin): string;
	static GetPinIndex(A: JavascriptEdGraphPin): number;
	static GetPinGUID(A: JavascriptEdGraphPin): Guid;
	static GetPinContainerType(A: JavascriptEdGraphPin): EJavascriptPinContainerType;
	static GetParentPin(A: JavascriptEdGraphPin): JavascriptEdGraphPin;
	static GetOwningNode(A: JavascriptEdGraphPin): EdGraphNode;
	static GetOwnerPanel(UNode: JavascriptGraphEdNode): JavascriptSlateWidget;
	static GetOutputPinWidget(Container: JavascriptDetermineLinkGeometryContainer): JavascriptPinWidget;
	static GetLinkedTo(A: JavascriptEdGraphPin): JavascriptEdGraphPin[];
	static GetLinkedPinNum(A: JavascriptEdGraphPin): number;
	static GetHorveredPinNum(Container: JavascriptGraphConnectionDrawingPolicyContainer): number;
	static GetDirection(A: JavascriptEdGraphPin): EEdGraphPinDirection;
	static GetDefaultObject(): JavascriptEdGraphPin;
	static GetArrangedNodes(Container: JavascriptDetermineLinkGeometryContainer,UNode: EdGraphNode): JavascriptArrangedWidget;
	static FindPinToPinWidgetMap(Container: JavascriptDetermineLinkGeometryContainer,Pin: JavascriptEdGraphPin): JavascriptPinWidget;
	static FindPinGeometries(Container: JavascriptDetermineLinkGeometryContainer,PinWidget: JavascriptPinWidget): JavascriptArrangedWidget;
	static FindPin(UNode: EdGraphNode,PinName: string,Direction: EEdGraphPinDirection): JavascriptEdGraphPin;
	static FindClosestPointOnGeom(Geom: Geometry,TestPoint: Vector2D): Vector2D;
	static Finalize(Creator?: JavascriptNodeCreator): {Creator: JavascriptNodeCreator};
	static DrawSplineWithArrow(Container: JavascriptGraphConnectionDrawingPolicyContainer,StartAnchorPoint: Vector2D,EndAnchorPoint: Vector2D,Params: JavascriptConnectionParams): void;
	static DrawConnection(Container: JavascriptGraphConnectionDrawingPolicyContainer,A: Vector2D,B: Vector2D,Params: JavascriptConnectionParams): void;
	static DetermineWiringStyle(Container: JavascriptGraphConnectionDrawingPolicyContainer,OutputPin: JavascriptEdGraphPin,InputPin: JavascriptEdGraphPin,Params?: JavascriptConnectionParams): {Params: JavascriptConnectionParams};
	static DestroyNode(UNode: EdGraphNode): void;
	static CustomNodeCreator(Graph: JavascriptGraphEdGraph): JavascriptNodeCreator;
	static CenterOf(Geom: Geometry): Vector2D;
	static CanUserDeleteNode(UNode: EdGraphNode): boolean;
	static CanDuplicateNode(UNode: EdGraphNode): boolean;
	static BreakLinkTo(A: JavascriptEdGraphPin,B: JavascriptEdGraphPin): void;
	static BreakAllPinLinks(A: JavascriptEdGraphPin): void;
	static AutowireNewNode(UNode: EdGraphNode,FromPin: JavascriptEdGraphPin): void;
	static ApplyHoverDeemphasis(Container: JavascriptGraphConnectionDrawingPolicyContainer,OutputPin: JavascriptEdGraphPin,InputPin: JavascriptEdGraphPin,Thickness: number,WireColor: LinearColor): void;
	static AddPinToHoverSet(InSlateEdNode: JavascriptSlateEdNode,Pin: JavascriptEdGraphPin): void;
	static C(Other: UObject | any): JavascriptGraphEditorLibrary;
}

declare class JavascriptGraphAppearanceInfo { 
	CornerImage: SlateBrush;
	CornerText: string;
	PIENotifyText: string;
	ReadOnlyText: string;
	InstructionText: string;
	clone() : JavascriptGraphAppearanceInfo;
	static C(Other: UObject | any): JavascriptGraphAppearanceInfo;
}

declare type EPinVisibility = 'Pin_Show' | 'Pin_HideNoConnection' | 'Pin_HideNoConnectionNoDefault' | 'Pin_MAX';
declare var EPinVisibility : { Pin_Show:'Pin_Show',Pin_HideNoConnection:'Pin_HideNoConnection',Pin_HideNoConnectionNoDefault:'Pin_HideNoConnectionNoDefault',Pin_MAX:'Pin_MAX', };
declare class JavascriptGraphEditorWidget extends Widget { 
	EdGraph: JavascriptGraphEdGraph;
	OnNodeDoubleClicked: UnrealEngineDelegate<(UNode: EdGraphNode) => void>;
	OnDropActor: UnrealEngineDelegate<(Actors: Actor[], Graph: EdGraph, Point: Vector2D) => void>;
	OnDisallowedPinConnection: UnrealEngineDelegate<(A: JavascriptEdGraphPin, B: JavascriptEdGraphPin) => void>;
	OnSelectedNodesChanged: UnrealEngineDelegate<(Set: UObject[]) => void>;
	AppearanceInfo: JavascriptGraphAppearanceInfo;
	CommandList: JavascriptUICommandList;
	static Load(ResourceName: string): JavascriptGraphEditorWidget;
	static Find(Outer: UObject, ResourceName: string): JavascriptGraphEditorWidget;
	static GetDefaultObject(): JavascriptGraphEditorWidget;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGraphEditorWidget;
	SetViewLocation(Location: Vector2D,ZoomAmount: number): void;
	SetPinVisibility(InVisibility: EPinVisibility): void;
	SetNodeSelection(UNode: EdGraphNode,bSelect: boolean): void;
	SetGraph(InEdGraph: JavascriptGraphEdGraph): void;
	SelectAllNodes(): void;
	NotifyGraphChanged(): void;
	static NewGraph(ParentScope: UObject): JavascriptGraphEdGraph;
	JumpToPin(JumpToMe: JavascriptEdGraphPin): void;
	JumpToNode(JumpToMe: EdGraphNode,bRequestRename: boolean,bSelectNode: boolean): void;
	GetViewLocation(OutLocation?: Vector2D,OutZoomAmount?: number): {OutLocation: Vector2D, OutZoomAmount: number};
	GetSelectedNodes(): UObject[];
	GetPasteLocation(): Vector2D;
	ClearSelectionSet(): void;
	static C(Other: UObject | any): JavascriptGraphEditorWidget;
}

declare class JavascriptGraphEdNodeWidget extends Widget { 
	EdNode: JavascriptGraphEdNode;
	static Load(ResourceName: string): JavascriptGraphEdNodeWidget;
	static Find(Outer: UObject, ResourceName: string): JavascriptGraphEdNodeWidget;
	static GetDefaultObject(): JavascriptGraphEdNodeWidget;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGraphEdNodeWidget;
	SetNode(InEdNode: JavascriptGraphEdNode): void;
	static C(Other: UObject | any): JavascriptGraphEdNodeWidget;
}

declare class JavascriptTextProperty { 
	Key: string;
	Namespace: string;
	Value: string;
	TableId: string;
	clone() : JavascriptTextProperty;
	static C(Other: UObject | any): JavascriptTextProperty;
}

declare class JavascriptGraphTextPropertyEditableTextBox extends Widget { 
	OnGetGraphPin: UnrealEngineDelegate<() => JavascriptEdGraphPin>;
	OnGetDefaultValue: UnrealEngineDelegate<() => JavascriptTextProperty>;
	OnTextCommitted: UnrealEngineMulticastDelegate<(TextProperty: JavascriptTextProperty) => void>;
	WidgetStyle: EditableTextBoxStyle;
	WrapTextAt: number;
	AutoWrapText: boolean;
	static Load(ResourceName: string): JavascriptGraphTextPropertyEditableTextBox;
	static Find(Outer: UObject, ResourceName: string): JavascriptGraphTextPropertyEditableTextBox;
	static GetDefaultObject(): JavascriptGraphTextPropertyEditableTextBox;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGraphTextPropertyEditableTextBox;
	static C(Other: UObject | any): JavascriptGraphTextPropertyEditableTextBox;
}

declare class OnGetDefaultValue__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetDefaultValue__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetDefaultValue__PythonCallable;
	static GetDefaultObject(): OnGetDefaultValue__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetDefaultValue__PythonCallable;
	static C(Other: UObject | any): OnGetDefaultValue__PythonCallable;
}

declare class OnGetGraphPin__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetGraphPin__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetGraphPin__PythonCallable;
	static GetDefaultObject(): OnGetGraphPin__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetGraphPin__PythonCallable;
	static C(Other: UObject | any): OnGetGraphPin__PythonCallable;
}

declare class OnDisallowedPinConnection__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDisallowedPinConnection__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDisallowedPinConnection__PythonCallable;
	static GetDefaultObject(): OnDisallowedPinConnection__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDisallowedPinConnection__PythonCallable;
	static C(Other: UObject | any): OnDisallowedPinConnection__PythonCallable;
}

declare class OnDropActor__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDropActor__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDropActor__PythonCallable;
	static GetDefaultObject(): OnDropActor__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDropActor__PythonCallable;
	static C(Other: UObject | any): OnDropActor__PythonCallable;
}

declare class SetNodes__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): SetNodes__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): SetNodes__PythonCallable;
	static GetDefaultObject(): SetNodes__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SetNodes__PythonCallable;
	static C(Other: UObject | any): SetNodes__PythonCallable;
}

declare class SingleNode__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): SingleNode__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): SingleNode__PythonCallable;
	static GetDefaultObject(): SingleNode__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SingleNode__PythonCallable;
	static C(Other: UObject | any): SingleNode__PythonCallable;
}

declare class OnBuildMenu__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnBuildMenu__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnBuildMenu__PythonCallable;
	static GetDefaultObject(): OnBuildMenu__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnBuildMenu__PythonCallable;
	static C(Other: UObject | any): OnBuildMenu__PythonCallable;
}

declare class OnCanCreateConnection__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnCanCreateConnection__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnCanCreateConnection__PythonCallable;
	static GetDefaultObject(): OnCanCreateConnection__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnCanCreateConnection__PythonCallable;
	static C(Other: UObject | any): OnCanCreateConnection__PythonCallable;
}

declare class OnContextActions__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnContextActions__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnContextActions__PythonCallable;
	static GetDefaultObject(): OnContextActions__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnContextActions__PythonCallable;
	static C(Other: UObject | any): OnContextActions__PythonCallable;
}

declare class OnCreateAutomaticConversionNodeAndConnections__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnCreateAutomaticConversionNodeAndConnections__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnCreateAutomaticConversionNodeAndConnections__PythonCallable;
	static GetDefaultObject(): OnCreateAutomaticConversionNodeAndConnections__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnCreateAutomaticConversionNodeAndConnections__PythonCallable;
	static C(Other: UObject | any): OnCreateAutomaticConversionNodeAndConnections__PythonCallable;
}

declare class OnCreatePin__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnCreatePin__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnCreatePin__PythonCallable;
	static GetDefaultObject(): OnCreatePin__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnCreatePin__PythonCallable;
	static C(Other: UObject | any): OnCreatePin__PythonCallable;
}

declare class OnDetermineLinkGeometry__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDetermineLinkGeometry__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDetermineLinkGeometry__PythonCallable;
	static GetDefaultObject(): OnDetermineLinkGeometry__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDetermineLinkGeometry__PythonCallable;
	static C(Other: UObject | any): OnDetermineLinkGeometry__PythonCallable;
}

declare class OnDetermineWiringStyle__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDetermineWiringStyle__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDetermineWiringStyle__PythonCallable;
	static GetDefaultObject(): OnDetermineWiringStyle__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDetermineWiringStyle__PythonCallable;
	static C(Other: UObject | any): OnDetermineWiringStyle__PythonCallable;
}

declare class OnDrawPreviewConnector__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDrawPreviewConnector__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDrawPreviewConnector__PythonCallable;
	static GetDefaultObject(): OnDrawPreviewConnector__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDrawPreviewConnector__PythonCallable;
	static C(Other: UObject | any): OnDrawPreviewConnector__PythonCallable;
}

declare class OnDrawSplineWithArrow__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDrawSplineWithArrow__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDrawSplineWithArrow__PythonCallable;
	static GetDefaultObject(): OnDrawSplineWithArrow__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDrawSplineWithArrow__PythonCallable;
	static C(Other: UObject | any): OnDrawSplineWithArrow__PythonCallable;
}

declare class OnDrawSplineWithArrow_Geom__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDrawSplineWithArrow_Geom__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDrawSplineWithArrow_Geom__PythonCallable;
	static GetDefaultObject(): OnDrawSplineWithArrow_Geom__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDrawSplineWithArrow_Geom__PythonCallable;
	static C(Other: UObject | any): OnDrawSplineWithArrow_Geom__PythonCallable;
}

declare class OnEdNodeAction__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnEdNodeAction__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnEdNodeAction__PythonCallable;
	static GetDefaultObject(): OnEdNodeAction__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnEdNodeAction__PythonCallable;
	static C(Other: UObject | any): OnEdNodeAction__PythonCallable;
}

declare class OnGetBoolean__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetBoolean__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetBoolean__PythonCallable;
	static GetDefaultObject(): OnGetBoolean__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetBoolean__PythonCallable;
	static C(Other: UObject | any): OnGetBoolean__PythonCallable;
}

declare class OnGetBoolean_GraphPin__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetBoolean_GraphPin__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetBoolean_GraphPin__PythonCallable;
	static GetDefaultObject(): OnGetBoolean_GraphPin__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetBoolean_GraphPin__PythonCallable;
	static C(Other: UObject | any): OnGetBoolean_GraphPin__PythonCallable;
}

declare class OnGetBooleanMoveTo__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetBooleanMoveTo__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetBooleanMoveTo__PythonCallable;
	static GetDefaultObject(): OnGetBooleanMoveTo__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetBooleanMoveTo__PythonCallable;
	static C(Other: UObject | any): OnGetBooleanMoveTo__PythonCallable;
}

declare class OnGetBooleanWidget__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetBooleanWidget__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetBooleanWidget__PythonCallable;
	static GetDefaultObject(): OnGetBooleanWidget__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetBooleanWidget__PythonCallable;
	static C(Other: UObject | any): OnGetBooleanWidget__PythonCallable;
}

declare class OnGetCustomPinBoxWidget__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetCustomPinBoxWidget__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetCustomPinBoxWidget__PythonCallable;
	static GetDefaultObject(): OnGetCustomPinBoxWidget__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetCustomPinBoxWidget__PythonCallable;
	static C(Other: UObject | any): OnGetCustomPinBoxWidget__PythonCallable;
}

declare class OnGetPinColor__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetPinColor__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetPinColor__PythonCallable;
	static GetDefaultObject(): OnGetPinColor__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetPinColor__PythonCallable;
	static C(Other: UObject | any): OnGetPinColor__PythonCallable;
}

declare class OnGetPins__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetPins__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetPins__PythonCallable;
	static GetDefaultObject(): OnGetPins__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetPins__PythonCallable;
	static C(Other: UObject | any): OnGetPins__PythonCallable;
}

declare class OnGetSlateBrushName__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetSlateBrushName__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetSlateBrushName__PythonCallable;
	static GetDefaultObject(): OnGetSlateBrushName__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetSlateBrushName__PythonCallable;
	static C(Other: UObject | any): OnGetSlateBrushName__PythonCallable;
}

declare class OnGetString__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetString__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetString__PythonCallable;
	static GetDefaultObject(): OnGetString__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetString__PythonCallable;
	static C(Other: UObject | any): OnGetString__PythonCallable;
}

declare class OnMouseDragEvent__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnMouseDragEvent__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnMouseDragEvent__PythonCallable;
	static GetDefaultObject(): OnMouseDragEvent__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnMouseDragEvent__PythonCallable;
	static C(Other: UObject | any): OnMouseDragEvent__PythonCallable;
}

declare class OnMouseEvent__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnMouseEvent__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnMouseEvent__PythonCallable;
	static GetDefaultObject(): OnMouseEvent__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnMouseEvent__PythonCallable;
	static C(Other: UObject | any): OnMouseEvent__PythonCallable;
}

declare class OnMouseEventAdvanced__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnMouseEventAdvanced__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnMouseEventAdvanced__PythonCallable;
	static GetDefaultObject(): OnMouseEventAdvanced__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnMouseEventAdvanced__PythonCallable;
	static C(Other: UObject | any): OnMouseEventAdvanced__PythonCallable;
}

declare class OnPerformAction__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnPerformAction__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnPerformAction__PythonCallable;
	static GetDefaultObject(): OnPerformAction__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnPerformAction__PythonCallable;
	static C(Other: UObject | any): OnPerformAction__PythonCallable;
}

declare class OnPerformSecondPassLayout__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnPerformSecondPassLayout__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnPerformSecondPassLayout__PythonCallable;
	static GetDefaultObject(): OnPerformSecondPassLayout__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnPerformSecondPassLayout__PythonCallable;
	static C(Other: UObject | any): OnPerformSecondPassLayout__PythonCallable;
}

declare class OnPinConnectionListChanged__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnPinConnectionListChanged__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnPinConnectionListChanged__PythonCallable;
	static GetDefaultObject(): OnPinConnectionListChanged__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnPinConnectionListChanged__PythonCallable;
	static C(Other: UObject | any): OnPinConnectionListChanged__PythonCallable;
}

declare class OnShouldAlwaysPurgeOnModification__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnShouldAlwaysPurgeOnModification__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnShouldAlwaysPurgeOnModification__PythonCallable;
	static GetDefaultObject(): OnShouldAlwaysPurgeOnModification__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnShouldAlwaysPurgeOnModification__PythonCallable;
	static C(Other: UObject | any): OnShouldAlwaysPurgeOnModification__PythonCallable;
}

declare class OnTakeContentWidget__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnTakeContentWidget__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnTakeContentWidget__PythonCallable;
	static GetDefaultObject(): OnTakeContentWidget__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnTakeContentWidget__PythonCallable;
	static C(Other: UObject | any): OnTakeContentWidget__PythonCallable;
}

declare class OnTakeWidget__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnTakeWidget__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnTakeWidget__PythonCallable;
	static GetDefaultObject(): OnTakeWidget__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnTakeWidget__PythonCallable;
	static C(Other: UObject | any): OnTakeWidget__PythonCallable;
}

declare class OnTryCreateConnection__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnTryCreateConnection__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnTryCreateConnection__PythonCallable;
	static GetDefaultObject(): OnTryCreateConnection__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnTryCreateConnection__PythonCallable;
	static C(Other: UObject | any): OnTryCreateConnection__PythonCallable;
}

declare class OnVectorArith__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnVectorArith__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnVectorArith__PythonCallable;
	static GetDefaultObject(): OnVectorArith__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnVectorArith__PythonCallable;
	static C(Other: UObject | any): OnVectorArith__PythonCallable;
}

declare class DynamicSimpleGetBoolDelegate__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): DynamicSimpleGetBoolDelegate__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): DynamicSimpleGetBoolDelegate__PythonCallable;
	static GetDefaultObject(): DynamicSimpleGetBoolDelegate__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): DynamicSimpleGetBoolDelegate__PythonCallable;
	static C(Other: UObject | any): DynamicSimpleGetBoolDelegate__PythonCallable;
}

declare class OnGenerateInvalidCellWidget__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGenerateInvalidCellWidget__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGenerateInvalidCellWidget__PythonCallable;
	static GetDefaultObject(): OnGenerateInvalidCellWidget__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGenerateInvalidCellWidget__PythonCallable;
	static C(Other: UObject | any): OnGenerateInvalidCellWidget__PythonCallable;
}

declare class PropertyEditorPropertyChanged__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): PropertyEditorPropertyChanged__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): PropertyEditorPropertyChanged__PythonCallable;
	static GetDefaultObject(): PropertyEditorPropertyChanged__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): PropertyEditorPropertyChanged__PythonCallable;
	static C(Other: UObject | any): PropertyEditorPropertyChanged__PythonCallable;
}

declare class OnBeforePopup__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnBeforePopup__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnBeforePopup__PythonCallable;
	static GetDefaultObject(): OnBeforePopup__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnBeforePopup__PythonCallable;
	static C(Other: UObject | any): OnBeforePopup__PythonCallable;
}

declare class OnUrlChanged__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnUrlChanged__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnUrlChanged__PythonCallable;
	static GetDefaultObject(): OnUrlChanged__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnUrlChanged__PythonCallable;
	static C(Other: UObject | any): OnUrlChanged__PythonCallable;
}

declare class OnHook__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnHook__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnHook__PythonCallable;
	static GetDefaultObject(): OnHook__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnHook__PythonCallable;
	static C(Other: UObject | any): OnHook__PythonCallable;
}

declare class JavascriptCanExecuteAction__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): JavascriptCanExecuteAction__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): JavascriptCanExecuteAction__PythonCallable;
	static GetDefaultObject(): JavascriptCanExecuteAction__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptCanExecuteAction__PythonCallable;
	static C(Other: UObject | any): JavascriptCanExecuteAction__PythonCallable;
}

declare class JavascriptExecuteAction__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): JavascriptExecuteAction__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): JavascriptExecuteAction__PythonCallable;
	static GetDefaultObject(): JavascriptExecuteAction__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptExecuteAction__PythonCallable;
	static C(Other: UObject | any): JavascriptExecuteAction__PythonCallable;
}

declare class OnClick_Backward__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnClick_Backward__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnClick_Backward__PythonCallable;
	static GetDefaultObject(): OnClick_Backward__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnClick_Backward__PythonCallable;
	static C(Other: UObject | any): OnClick_Backward__PythonCallable;
}

declare class OnClick_Backward_End__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnClick_Backward_End__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnClick_Backward_End__PythonCallable;
	static GetDefaultObject(): OnClick_Backward_End__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnClick_Backward_End__PythonCallable;
	static C(Other: UObject | any): OnClick_Backward_End__PythonCallable;
}

declare class OnClick_Backward_Step__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnClick_Backward_Step__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnClick_Backward_Step__PythonCallable;
	static GetDefaultObject(): OnClick_Backward_Step__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnClick_Backward_Step__PythonCallable;
	static C(Other: UObject | any): OnClick_Backward_Step__PythonCallable;
}

declare class OnClick_Forward__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnClick_Forward__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnClick_Forward__PythonCallable;
	static GetDefaultObject(): OnClick_Forward__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnClick_Forward__PythonCallable;
	static C(Other: UObject | any): OnClick_Forward__PythonCallable;
}

declare class OnClick_Forward_End__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnClick_Forward_End__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnClick_Forward_End__PythonCallable;
	static GetDefaultObject(): OnClick_Forward_End__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnClick_Forward_End__PythonCallable;
	static C(Other: UObject | any): OnClick_Forward_End__PythonCallable;
}

declare class OnClick_Forward_Step__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnClick_Forward_Step__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnClick_Forward_Step__PythonCallable;
	static GetDefaultObject(): OnClick_Forward_Step__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnClick_Forward_Step__PythonCallable;
	static C(Other: UObject | any): OnClick_Forward_Step__PythonCallable;
}

declare class OnClick_ToggleLoop__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnClick_ToggleLoop__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnClick_ToggleLoop__PythonCallable;
	static GetDefaultObject(): OnClick_ToggleLoop__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnClick_ToggleLoop__PythonCallable;
	static C(Other: UObject | any): OnClick_ToggleLoop__PythonCallable;
}

declare class SetPlaybackPosition__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): SetPlaybackPosition__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): SetPlaybackPosition__PythonCallable;
	static GetDefaultObject(): SetPlaybackPosition__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SetPlaybackPosition__PythonCallable;
	static C(Other: UObject | any): SetPlaybackPosition__PythonCallable;
}

declare class CustomChildren__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): CustomChildren__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): CustomChildren__PythonCallable;
	static GetDefaultObject(): CustomChildren__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): CustomChildren__PythonCallable;
	static C(Other: UObject | any): CustomChildren__PythonCallable;
}

declare class CustomHeader__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): CustomHeader__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): CustomHeader__PythonCallable;
	static GetDefaultObject(): CustomHeader__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): CustomHeader__PythonCallable;
	static C(Other: UObject | any): CustomHeader__PythonCallable;
}

declare class OnDestroy__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDestroy__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDestroy__PythonCallable;
	static GetDefaultObject(): OnDestroy__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDestroy__PythonCallable;
	static C(Other: UObject | any): OnDestroy__PythonCallable;
}

declare class CheckDelegate__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): CheckDelegate__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): CheckDelegate__PythonCallable;
	static GetDefaultObject(): CheckDelegate__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): CheckDelegate__PythonCallable;
	static C(Other: UObject | any): CheckDelegate__PythonCallable;
}

declare class SimpleDelegate__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): SimpleDelegate__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): SimpleDelegate__PythonCallable;
	static GetDefaultObject(): SimpleDelegate__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SimpleDelegate__PythonCallable;
	static C(Other: UObject | any): SimpleDelegate__PythonCallable;
}

declare class OnNewLogMessage__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnNewLogMessage__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnNewLogMessage__PythonCallable;
	static GetDefaultObject(): OnNewLogMessage__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnNewLogMessage__PythonCallable;
	static C(Other: UObject | any): OnNewLogMessage__PythonCallable;
}

declare class ActorDuplicated__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): ActorDuplicated__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): ActorDuplicated__PythonCallable;
	static GetDefaultObject(): ActorDuplicated__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ActorDuplicated__PythonCallable;
	static C(Other: UObject | any): ActorDuplicated__PythonCallable;
}

declare class OnClick__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnClick__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnClick__PythonCallable;
	static GetDefaultObject(): OnClick__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnClick__PythonCallable;
	static C(Other: UObject | any): OnClick__PythonCallable;
}

declare class OnDraw__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDraw__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDraw__PythonCallable;
	static GetDefaultObject(): OnDraw__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDraw__PythonCallable;
	static C(Other: UObject | any): OnDraw__PythonCallable;
}

declare class OnDrawHUD__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnDrawHUD__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnDrawHUD__PythonCallable;
	static GetDefaultObject(): OnDrawHUD__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnDrawHUD__PythonCallable;
	static C(Other: UObject | any): OnDrawHUD__PythonCallable;
}

declare class OnGetAction__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetAction__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetAction__PythonCallable;
	static GetDefaultObject(): OnGetAction__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetAction__PythonCallable;
	static C(Other: UObject | any): OnGetAction__PythonCallable;
}

declare class OnGetWidget__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetWidget__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetWidget__PythonCallable;
	static GetDefaultObject(): OnGetWidget__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetWidget__PythonCallable;
	static C(Other: UObject | any): OnGetWidget__PythonCallable;
}

declare class OnIsCompatibleWith__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnIsCompatibleWith__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnIsCompatibleWith__PythonCallable;
	static GetDefaultObject(): OnIsCompatibleWith__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnIsCompatibleWith__PythonCallable;
	static C(Other: UObject | any): OnIsCompatibleWith__PythonCallable;
}

declare class OnProcess__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnProcess__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnProcess__PythonCallable;
	static GetDefaultObject(): OnProcess__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnProcess__PythonCallable;
	static C(Other: UObject | any): OnProcess__PythonCallable;
}

declare class OnSelect__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnSelect__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnSelect__PythonCallable;
	static GetDefaultObject(): OnSelect__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnSelect__PythonCallable;
	static C(Other: UObject | any): OnSelect__PythonCallable;
}

declare class OnSelectionChanged__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnSelectionChanged__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnSelectionChanged__PythonCallable;
	static GetDefaultObject(): OnSelectionChanged__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnSelectionChanged__PythonCallable;
	static C(Other: UObject | any): OnSelectionChanged__PythonCallable;
}

declare class OnUsesToolkits__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnUsesToolkits__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnUsesToolkits__PythonCallable;
	static GetDefaultObject(): OnUsesToolkits__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnUsesToolkits__PythonCallable;
	static C(Other: UObject | any): OnUsesToolkits__PythonCallable;
}

declare class QueryVector__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): QueryVector__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): QueryVector__PythonCallable;
	static GetDefaultObject(): QueryVector__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): QueryVector__PythonCallable;
	static C(Other: UObject | any): QueryVector__PythonCallable;
}

declare class Viewport0__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): Viewport0__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): Viewport0__PythonCallable;
	static GetDefaultObject(): Viewport0__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): Viewport0__PythonCallable;
	static C(Other: UObject | any): Viewport0__PythonCallable;
}

declare class ViewportAxis__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): ViewportAxis__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): ViewportAxis__PythonCallable;
	static GetDefaultObject(): ViewportAxis__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ViewportAxis__PythonCallable;
	static C(Other: UObject | any): ViewportAxis__PythonCallable;
}

declare class ViewportDelta__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): ViewportDelta__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): ViewportDelta__PythonCallable;
	static GetDefaultObject(): ViewportDelta__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ViewportDelta__PythonCallable;
	static C(Other: UObject | any): ViewportDelta__PythonCallable;
}

declare class ViewportKey__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): ViewportKey__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): ViewportKey__PythonCallable;
	static GetDefaultObject(): ViewportKey__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ViewportKey__PythonCallable;
	static C(Other: UObject | any): ViewportKey__PythonCallable;
}

declare class ViewportXY__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): ViewportXY__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): ViewportXY__PythonCallable;
	static GetDefaultObject(): ViewportXY__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ViewportXY__PythonCallable;
	static C(Other: UObject | any): ViewportXY__PythonCallable;
}

declare class OnGetWidgetLocation__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetWidgetLocation__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetWidgetLocation__PythonCallable;
	static GetDefaultObject(): OnGetWidgetLocation__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetWidgetLocation__PythonCallable;
	static C(Other: UObject | any): OnGetWidgetLocation__PythonCallable;
}

declare class OnGetWidgetMode__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetWidgetMode__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetWidgetMode__PythonCallable;
	static GetDefaultObject(): OnGetWidgetMode__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetWidgetMode__PythonCallable;
	static C(Other: UObject | any): OnGetWidgetMode__PythonCallable;
}

declare class OnGetWidgetRotation__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnGetWidgetRotation__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnGetWidgetRotation__PythonCallable;
	static GetDefaultObject(): OnGetWidgetRotation__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnGetWidgetRotation__PythonCallable;
	static C(Other: UObject | any): OnGetWidgetRotation__PythonCallable;
}

declare class OnInputAxis__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnInputAxis__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnInputAxis__PythonCallable;
	static GetDefaultObject(): OnInputAxis__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnInputAxis__PythonCallable;
	static C(Other: UObject | any): OnInputAxis__PythonCallable;
}

declare class OnInputKey__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnInputKey__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnInputKey__PythonCallable;
	static GetDefaultObject(): OnInputKey__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnInputKey__PythonCallable;
	static C(Other: UObject | any): OnInputKey__PythonCallable;
}

declare class OnInputWidgetDelta__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnInputWidgetDelta__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnInputWidgetDelta__PythonCallable;
	static GetDefaultObject(): OnInputWidgetDelta__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnInputWidgetDelta__PythonCallable;
	static C(Other: UObject | any): OnInputWidgetDelta__PythonCallable;
}

declare class OnMouseEnter__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnMouseEnter__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnMouseEnter__PythonCallable;
	static GetDefaultObject(): OnMouseEnter__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnMouseEnter__PythonCallable;
	static C(Other: UObject | any): OnMouseEnter__PythonCallable;
}

declare class OnMouseLeave__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnMouseLeave__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnMouseLeave__PythonCallable;
	static GetDefaultObject(): OnMouseLeave__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnMouseLeave__PythonCallable;
	static C(Other: UObject | any): OnMouseLeave__PythonCallable;
}

declare class OnMouseMove__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnMouseMove__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnMouseMove__PythonCallable;
	static GetDefaultObject(): OnMouseMove__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnMouseMove__PythonCallable;
	static C(Other: UObject | any): OnMouseMove__PythonCallable;
}

declare class OnViewportClick__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnViewportClick__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnViewportClick__PythonCallable;
	static GetDefaultObject(): OnViewportClick__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnViewportClick__PythonCallable;
	static C(Other: UObject | any): OnViewportClick__PythonCallable;
}

declare class OnViewportDraw__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnViewportDraw__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnViewportDraw__PythonCallable;
	static GetDefaultObject(): OnViewportDraw__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnViewportDraw__PythonCallable;
	static C(Other: UObject | any): OnViewportDraw__PythonCallable;
}

declare class OnViewportDrawCanvas__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnViewportDrawCanvas__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnViewportDrawCanvas__PythonCallable;
	static GetDefaultObject(): OnViewportDrawCanvas__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnViewportDrawCanvas__PythonCallable;
	static C(Other: UObject | any): OnViewportDrawCanvas__PythonCallable;
}

declare class OnViewportTrackingStarted__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnViewportTrackingStarted__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnViewportTrackingStarted__PythonCallable;
	static GetDefaultObject(): OnViewportTrackingStarted__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnViewportTrackingStarted__PythonCallable;
	static C(Other: UObject | any): OnViewportTrackingStarted__PythonCallable;
}

declare class OnViewportTrackingStopped__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnViewportTrackingStopped__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnViewportTrackingStopped__PythonCallable;
	static GetDefaultObject(): OnViewportTrackingStopped__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnViewportTrackingStopped__PythonCallable;
	static C(Other: UObject | any): OnViewportTrackingStopped__PythonCallable;
}

declare class JavascriptEditorTickSignature__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): JavascriptEditorTickSignature__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): JavascriptEditorTickSignature__PythonCallable;
	static GetDefaultObject(): JavascriptEditorTickSignature__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptEditorTickSignature__PythonCallable;
	static C(Other: UObject | any): JavascriptEditorTickSignature__PythonCallable;
}

declare class CloseTab__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): CloseTab__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): CloseTab__PythonCallable;
	static GetDefaultObject(): CloseTab__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): CloseTab__PythonCallable;
	static C(Other: UObject | any): CloseTab__PythonCallable;
}

declare class OnTabActivated__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnTabActivated__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnTabActivated__PythonCallable;
	static GetDefaultObject(): OnTabActivated__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnTabActivated__PythonCallable;
	static C(Other: UObject | any): OnTabActivated__PythonCallable;
}

declare class SpawnTab__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): SpawnTab__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): SpawnTab__PythonCallable;
	static GetDefaultObject(): SpawnTab__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): SpawnTab__PythonCallable;
	static C(Other: UObject | any): SpawnTab__PythonCallable;
}

declare class JavascriptGetExtender__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): JavascriptGetExtender__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): JavascriptGetExtender__PythonCallable;
	static GetDefaultObject(): JavascriptGetExtender__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): JavascriptGetExtender__PythonCallable;
	static C(Other: UObject | any): JavascriptGetExtender__PythonCallable;
}

declare class OnColorChangedEvent__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnColorChangedEvent__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnColorChangedEvent__PythonCallable;
	static GetDefaultObject(): OnColorChangedEvent__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnColorChangedEvent__PythonCallable;
	static C(Other: UObject | any): OnColorChangedEvent__PythonCallable;
}

declare class OnSetDefaultValue__PythonCallable extends PythonCallableForDelegate { 
	static Load(ResourceName: string): OnSetDefaultValue__PythonCallable;
	static Find(Outer: UObject, ResourceName: string): OnSetDefaultValue__PythonCallable;
	static GetDefaultObject(): OnSetDefaultValue__PythonCallable;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): OnSetDefaultValue__PythonCallable;
	static C(Other: UObject | any): OnSetDefaultValue__PythonCallable;
}

declare class AudioSynesthesiaNRTFactory extends Factory { 
	AudioSynesthesiaNRTClass: UnrealEngineClass;
	static Load(ResourceName: string): AudioSynesthesiaNRTFactory;
	static Find(Outer: UObject, ResourceName: string): AudioSynesthesiaNRTFactory;
	static GetDefaultObject(): AudioSynesthesiaNRTFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioSynesthesiaNRTFactory;
	static C(Other: UObject | any): AudioSynesthesiaNRTFactory;
}

declare class AudioSynesthesiaNRTSettingsFactory extends Factory { 
	AudioSynesthesiaNRTSettingsClass: UnrealEngineClass;
	static Load(ResourceName: string): AudioSynesthesiaNRTSettingsFactory;
	static Find(Outer: UObject, ResourceName: string): AudioSynesthesiaNRTSettingsFactory;
	static GetDefaultObject(): AudioSynesthesiaNRTSettingsFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioSynesthesiaNRTSettingsFactory;
	static C(Other: UObject | any): AudioSynesthesiaNRTSettingsFactory;
}

declare class AudioSynesthesiaSettingsFactory extends Factory { 
	AudioSynesthesiaSettingsClass: UnrealEngineClass;
	static Load(ResourceName: string): AudioSynesthesiaSettingsFactory;
	static Find(Outer: UObject, ResourceName: string): AudioSynesthesiaSettingsFactory;
	static GetDefaultObject(): AudioSynesthesiaSettingsFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AudioSynesthesiaSettingsFactory;
	static C(Other: UObject | any): AudioSynesthesiaSettingsFactory;
}

declare class LevelInstanceEditorMode extends EdMode { 
	static Load(ResourceName: string): LevelInstanceEditorMode;
	static Find(Outer: UObject, ResourceName: string): LevelInstanceEditorMode;
	static GetDefaultObject(): LevelInstanceEditorMode;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): LevelInstanceEditorMode;
	static C(Other: UObject | any): LevelInstanceEditorMode;
}

declare class LevelInstanceEditorSettings extends UObject { 
	TemplateMapInfos: TemplateMapInfo[];
	static Load(ResourceName: string): LevelInstanceEditorSettings;
	static Find(Outer: UObject, ResourceName: string): LevelInstanceEditorSettings;
	static GetDefaultObject(): LevelInstanceEditorSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): LevelInstanceEditorSettings;
	static C(Other: UObject | any): LevelInstanceEditorSettings;
}

declare class MockAI extends UObject { 
	Actor: Actor;
	BBComp: BlackboardComponent;
	BrainComp: BrainComponent;
	PerceptionComp: AIPerceptionComponent;
	PawnActionComp: PawnActionsComponent;
	static Load(ResourceName: string): MockAI;
	static Find(Outer: UObject, ResourceName: string): MockAI;
	static GetDefaultObject(): MockAI;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MockAI;
	static C(Other: UObject | any): MockAI;
}

declare class MockAI_BT extends MockAI { 
	BTComp: BehaviorTreeComponent;
	static Load(ResourceName: string): MockAI_BT;
	static Find(Outer: UObject, ResourceName: string): MockAI_BT;
	static GetDefaultObject(): MockAI_BT;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MockAI_BT;
	static C(Other: UObject | any): MockAI_BT;
}

declare class MockTask_Log extends GameplayTask { 
	static Load(ResourceName: string): MockTask_Log;
	static Find(Outer: UObject, ResourceName: string): MockTask_Log;
	static GetDefaultObject(): MockTask_Log;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MockTask_Log;
	static C(Other: UObject | any): MockTask_Log;
}

declare class MockGameplayTasksComponent extends GameplayTasksComponent { 
	static Load(ResourceName: string): MockGameplayTasksComponent;
	static Find(Outer: UObject, ResourceName: string): MockGameplayTasksComponent;
	static GetDefaultObject(): MockGameplayTasksComponent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MockGameplayTasksComponent;
	static C(Other: UObject | any): MockGameplayTasksComponent;
}

declare class MockGameplayTaskOwner extends UObject { 
	GTComponent: GameplayTasksComponent;
	static Load(ResourceName: string): MockGameplayTaskOwner;
	static Find(Outer: UObject, ResourceName: string): MockGameplayTaskOwner;
	static GetDefaultObject(): MockGameplayTaskOwner;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MockGameplayTaskOwner;
	static C(Other: UObject | any): MockGameplayTaskOwner;
}

declare class TestBTDecorator_Blackboard extends BTDecorator_Blackboard { 
	LogIndexBecomeRelevant: number;
	LogIndexCeaseRelevant: number;
	LogIndexCalculate: number;
	static Load(ResourceName: string): TestBTDecorator_Blackboard;
	static Find(Outer: UObject, ResourceName: string): TestBTDecorator_Blackboard;
	static GetDefaultObject(): TestBTDecorator_Blackboard;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestBTDecorator_Blackboard;
	static C(Other: UObject | any): TestBTDecorator_Blackboard;
}

declare class TestBTDecorator_CantExecute extends BTDecorator { 
	static Load(ResourceName: string): TestBTDecorator_CantExecute;
	static Find(Outer: UObject, ResourceName: string): TestBTDecorator_CantExecute;
	static GetDefaultObject(): TestBTDecorator_CantExecute;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestBTDecorator_CantExecute;
	static C(Other: UObject | any): TestBTDecorator_CantExecute;
}

declare class TestBTDecorator_DelayedAbort extends BTDecorator { 
	DelayTicks: number;
	bOnlyOnce: boolean;
	static Load(ResourceName: string): TestBTDecorator_DelayedAbort;
	static Find(Outer: UObject, ResourceName: string): TestBTDecorator_DelayedAbort;
	static GetDefaultObject(): TestBTDecorator_DelayedAbort;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestBTDecorator_DelayedAbort;
	static C(Other: UObject | any): TestBTDecorator_DelayedAbort;
}

declare class TestBTService_Log extends BTService { 
	LogActivation: number;
	LogDeactivation: number;
	KeyNameTick: string;
	KeyNameBecomeRelevant: string;
	KeyNameCeaseRelevant: string;
	LogTick: number;
	static Load(ResourceName: string): TestBTService_Log;
	static Find(Outer: UObject, ResourceName: string): TestBTService_Log;
	static GetDefaultObject(): TestBTService_Log;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestBTService_Log;
	static C(Other: UObject | any): TestBTService_Log;
}

declare class TestBTTask_LatentWithFlags extends BTTaskNode { 
	LogIndexExecuteStart: number;
	LogIndexExecuting: number;
	LogIndexExecuteFinish: number;
	LogIndexAbortStart: number;
	LogIndexAborting: number;
	LogIndexAbortFinish: number;
	ExecuteHalfTicks: number;
	AbortHalfTicks: number;
	KeyNameExecute: string;
	KeyNameAbort: string;
	LogResult: EBTNodeResult;
	static Load(ResourceName: string): TestBTTask_LatentWithFlags;
	static Find(Outer: UObject, ResourceName: string): TestBTTask_LatentWithFlags;
	static GetDefaultObject(): TestBTTask_LatentWithFlags;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestBTTask_LatentWithFlags;
	static C(Other: UObject | any): TestBTTask_LatentWithFlags;
}

declare class TestBTTask_Log extends BTTaskNode { 
	LogIndex: number;
	LogFinished: number;
	ExecutionTicks: number;
	LogTickIndex: number;
	LogResult: EBTNodeResult;
	static Load(ResourceName: string): TestBTTask_Log;
	static Find(Outer: UObject, ResourceName: string): TestBTTask_Log;
	static GetDefaultObject(): TestBTTask_Log;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestBTTask_Log;
	static C(Other: UObject | any): TestBTTask_Log;
}

declare class TestBTTask_SetFlag extends BTTaskNode { 
	KeyName: string;
	bValue: boolean;
	OnAbortKeyName: string;
	bOnAbortValue: boolean;
	TaskResult: EBTNodeResult;
	static Load(ResourceName: string): TestBTTask_SetFlag;
	static Find(Outer: UObject, ResourceName: string): TestBTTask_SetFlag;
	static GetDefaultObject(): TestBTTask_SetFlag;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestBTTask_SetFlag;
	static C(Other: UObject | any): TestBTTask_SetFlag;
}

declare class TestBTTask_SetValue extends BTTaskNode { 
	KeyName: string;
	Value: number;
	OnAbortKeyName: string;
	OnAbortValue: number;
	TaskResult: EBTNodeResult;
	static Load(ResourceName: string): TestBTTask_SetValue;
	static Find(Outer: UObject, ResourceName: string): TestBTTask_SetValue;
	static GetDefaultObject(): TestBTTask_SetValue;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestBTTask_SetValue;
	static C(Other: UObject | any): TestBTTask_SetValue;
}

declare class TestPawnAction_Log extends PawnAction { 
	static Load(ResourceName: string): TestPawnAction_Log;
	static Find(Outer: UObject, ResourceName: string): TestPawnAction_Log;
	static GetDefaultObject(): TestPawnAction_Log;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestPawnAction_Log;
	static C(Other: UObject | any): TestPawnAction_Log;
}

declare class TestPawnAction_CallFunction extends TestPawnAction_Log { 
	static Load(ResourceName: string): TestPawnAction_CallFunction;
	static Find(Outer: UObject, ResourceName: string): TestPawnAction_CallFunction;
	static GetDefaultObject(): TestPawnAction_CallFunction;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): TestPawnAction_CallFunction;
	static C(Other: UObject | any): TestPawnAction_CallFunction;
}

declare type ELiveCodingStartupMode = 'Automatic' | 'AutomaticButHidden' | 'Manual' | 'ELiveCodingStartupMode_MAX';
declare var ELiveCodingStartupMode : { Automatic:'Automatic',AutomaticButHidden:'AutomaticButHidden',Manual:'Manual',ELiveCodingStartupMode_MAX:'ELiveCodingStartupMode_MAX', };
declare class LiveCodingSettings extends UObject { 
	bEnabled: boolean;
	Startup: ELiveCodingStartupMode;
	bEnableReinstancing: boolean;
	bAutomaticallyCompileNewClasses: boolean;
	bPreloadEngineModules: boolean;
	bPreloadEnginePluginModules: boolean;
	bPreloadProjectModules: boolean;
	bPreloadProjectPluginModules: boolean;
	PreloadNamedModules: string[];
	static Load(ResourceName: string): LiveCodingSettings;
	static Find(Outer: UObject, ResourceName: string): LiveCodingSettings;
	static GetDefaultObject(): LiveCodingSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): LiveCodingSettings;
	static C(Other: UObject | any): LiveCodingSettings;
}

declare class NaniteAuditErrorArguments extends EditorConfigBase { 
	ProhibitUnsupportedBlendMode: boolean;
	ProhibitVertexInterpolator: boolean;
	ProhibitPixelDepthOffset: boolean;
	ProhibitWorldPositionOffset: boolean;
	static Load(ResourceName: string): NaniteAuditErrorArguments;
	static Find(Outer: UObject, ResourceName: string): NaniteAuditErrorArguments;
	static GetDefaultObject(): NaniteAuditErrorArguments;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): NaniteAuditErrorArguments;
	static C(Other: UObject | any): NaniteAuditErrorArguments;
}

declare class NaniteAuditOptimizeArguments extends EditorConfigBase { 
	TriangleThreshold: number;
	DisallowUnsupportedBlendMode: boolean;
	DisallowVertexInterpolator: boolean;
	DisallowPixelDepthOffset: boolean;
	DisallowWorldPositionOffset: boolean;
	static Load(ResourceName: string): NaniteAuditOptimizeArguments;
	static Find(Outer: UObject, ResourceName: string): NaniteAuditOptimizeArguments;
	static GetDefaultObject(): NaniteAuditOptimizeArguments;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): NaniteAuditOptimizeArguments;
	static C(Other: UObject | any): NaniteAuditOptimizeArguments;
}

declare class StructViewerProjectSettings extends UObject { 
	InternalOnlyPaths: DirectoryPath[];
	InternalOnlyStructs: ScriptStruct[];
	static Load(ResourceName: string): StructViewerProjectSettings;
	static Find(Outer: UObject, ResourceName: string): StructViewerProjectSettings;
	static GetDefaultObject(): StructViewerProjectSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): StructViewerProjectSettings;
	static C(Other: UObject | any): StructViewerProjectSettings;
}

declare class AnimationBlueprintEditorSettings extends UObject { 
	bPoseWatchSelectedNodes: boolean;
	bShowGraphCornerText: boolean;
	static Load(ResourceName: string): AnimationBlueprintEditorSettings;
	static Find(Outer: UObject, ResourceName: string): AnimationBlueprintEditorSettings;
	static GetDefaultObject(): AnimationBlueprintEditorSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AnimationBlueprintEditorSettings;
	static C(Other: UObject | any): AnimationBlueprintEditorSettings;
}

declare class LocalizationDashboardSettings extends UObject { 
	static Load(ResourceName: string): LocalizationDashboardSettings;
	static Find(Outer: UObject, ResourceName: string): LocalizationDashboardSettings;
	static GetDefaultObject(): LocalizationDashboardSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): LocalizationDashboardSettings;
	static C(Other: UObject | any): LocalizationDashboardSettings;
}

declare class MeshApproximationSettingsObject extends UObject { 
	Settings: MeshApproximationSettings;
	static Load(ResourceName: string): MeshApproximationSettingsObject;
	static Find(Outer: UObject, ResourceName: string): MeshApproximationSettingsObject;
	static GetDefaultObject(): MeshApproximationSettingsObject;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MeshApproximationSettingsObject;
	static C(Other: UObject | any): MeshApproximationSettingsObject;
}

declare class MeshInstancingSettings { 
	ActorClassToUse: UnrealEngineClass;
	InstanceReplacementThreshold: number;
	bSkipMeshesWithVertexColors: boolean;
	bUseHLODVolumes: boolean;
	ISMComponentToUse: UnrealEngineClass;
	clone() : MeshInstancingSettings;
	static C(Other: UObject | any): MeshInstancingSettings;
}

declare class MeshInstancingSettingsObject extends UObject { 
	Settings: MeshInstancingSettings;
	static Load(ResourceName: string): MeshInstancingSettingsObject;
	static Find(Outer: UObject, ResourceName: string): MeshInstancingSettingsObject;
	static GetDefaultObject(): MeshInstancingSettingsObject;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MeshInstancingSettingsObject;
	static C(Other: UObject | any): MeshInstancingSettingsObject;
}

declare class MeshMergingSettingsObject extends UObject { 
	Settings: MeshMergingSettings;
	static Load(ResourceName: string): MeshMergingSettingsObject;
	static Find(Outer: UObject, ResourceName: string): MeshMergingSettingsObject;
	static GetDefaultObject(): MeshMergingSettingsObject;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MeshMergingSettingsObject;
	static C(Other: UObject | any): MeshMergingSettingsObject;
}

declare class MeshProxySettingsObject extends UObject { 
	Settings: MeshProxySettings;
	static Load(ResourceName: string): MeshProxySettingsObject;
	static Find(Outer: UObject, ResourceName: string): MeshProxySettingsObject;
	static GetDefaultObject(): MeshProxySettingsObject;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): MeshProxySettingsObject;
	static C(Other: UObject | any): MeshProxySettingsObject;
}

declare class EditorKeyboardShortcutSettings extends DeveloperSettings { 
	static Load(ResourceName: string): EditorKeyboardShortcutSettings;
	static Find(Outer: UObject, ResourceName: string): EditorKeyboardShortcutSettings;
	static GetDefaultObject(): EditorKeyboardShortcutSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): EditorKeyboardShortcutSettings;
	static C(Other: UObject | any): EditorKeyboardShortcutSettings;
}

declare class HLODLayerFactory extends Factory { 
	static Load(ResourceName: string): HLODLayerFactory;
	static Find(Outer: UObject, ResourceName: string): HLODLayerFactory;
	static GetDefaultObject(): HLODLayerFactory;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): HLODLayerFactory;
	static C(Other: UObject | any): HLODLayerFactory;
}

declare class WorldPartitionConvertOptions extends UObject { 
	CommandletClass: UnrealEngineClass;
	bInPlace: boolean;
	bDeleteSourceLevels: boolean;
	bGenerateIni: boolean;
	bReportOnly: boolean;
	bVerbose: boolean;
	bSkipStableGUIDValidation: boolean;
	bOnlyMergeSubLevels: boolean;
	bSaveFoliageTypeToContentFolder: boolean;
	static Load(ResourceName: string): WorldPartitionConvertOptions;
	static Find(Outer: UObject, ResourceName: string): WorldPartitionConvertOptions;
	static GetDefaultObject(): WorldPartitionConvertOptions;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): WorldPartitionConvertOptions;
	static C(Other: UObject | any): WorldPartitionConvertOptions;
}

declare class WorldPartitionEditorSettings extends DeveloperSettings { 
	CommandletClass: UnrealEngineClass;
	InstancedFoliageGridSize: number;
	static Load(ResourceName: string): WorldPartitionEditorSettings;
	static Find(Outer: UObject, ResourceName: string): WorldPartitionEditorSettings;
	static GetDefaultObject(): WorldPartitionEditorSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): WorldPartitionEditorSettings;
	static C(Other: UObject | any): WorldPartitionEditorSettings;
}

declare type ESVGTheme = 'Dark' | 'Light' | 'ESVGTheme_MAX';
declare var ESVGTheme : { Dark:'Dark',Light:'Light',ESVGTheme_MAX:'ESVGTheme_MAX', };
declare class CSVtoSVGArugments extends EditorConfigBase { 
	CSV: FilePath;
	OutputDirectory: DirectoryPath;
	OutputFilename: string;
	skipRows: number;
	MinX: number;
	MaxX: number;
	MinY: number;
	MaxY: number;
	smooth: boolean;
	smoothKernelSize: number;
	smoothKernelPercent: number;
	Width: number;
	Height: number;
	Title: string;
	noMetadata: boolean;
	graphOnly: boolean;
	budget: number;
	Thickness: number;
	Theme: ESVGTheme;
	Threshold: number;
	stacked: boolean;
	stacktotalstack: string;
	Interactive: boolean;
	showaverages: boolean;
	colourOffset: number;
	averageThreshold: number;
	static Load(ResourceName: string): CSVtoSVGArugments;
	static Find(Outer: UObject, ResourceName: string): CSVtoSVGArugments;
	static GetDefaultObject(): CSVtoSVGArugments;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): CSVtoSVGArugments;
	static C(Other: UObject | any): CSVtoSVGArugments;
}

declare type EAndroidInstallLocation = 'InternalOnly' | 'PreferExternal' | 'Auto' | 'EAndroidInstallLocation_MAX';
declare var EAndroidInstallLocation : { InternalOnly:'InternalOnly',PreferExternal:'PreferExternal',Auto:'Auto',EAndroidInstallLocation_MAX:'EAndroidInstallLocation_MAX', };
declare type EAndroidScreenOrientation = 'Portrait' | 'ReversePortrait' | 'SensorPortrait' | 'Landscape' | 'ReverseLandscape' | 'SensorLandscape' | 'Sensor' | 'FullSensor' | 'EAndroidScreenOrientation_MAX';
declare var EAndroidScreenOrientation : { Portrait:'Portrait',ReversePortrait:'ReversePortrait',SensorPortrait:'SensorPortrait',Landscape:'Landscape',ReverseLandscape:'ReverseLandscape',SensorLandscape:'SensorLandscape',Sensor:'Sensor',FullSensor:'FullSensor',EAndroidScreenOrientation_MAX:'EAndroidScreenOrientation_MAX', };
declare type EAndroidDepthBufferPreference = 'Default' | 'Bits16' | 'Bits24' | 'Bits32' | 'EAndroidDepthBufferPreference_MAX';
declare var EAndroidDepthBufferPreference : { Default:'Default',Bits16:'Bits16',Bits24:'Bits24',Bits32:'Bits32',EAndroidDepthBufferPreference_MAX:'EAndroidDepthBufferPreference_MAX', };
declare type EOculusMobileDevice = 'Quest' | 'Quest2' | 'EOculusMobileDevice_MAX';
declare var EOculusMobileDevice : { Quest:'Quest',Quest2:'Quest2',EOculusMobileDevice_MAX:'EOculusMobileDevice_MAX', };
declare class GooglePlayAchievementMapping { 
	Name: string;
	AchievementID: string;
	clone() : GooglePlayAchievementMapping;
	static C(Other: UObject | any): GooglePlayAchievementMapping;
}

declare class GooglePlayLeaderboardMapping { 
	Name: string;
	LeaderboardID: string;
	clone() : GooglePlayLeaderboardMapping;
	static C(Other: UObject | any): GooglePlayLeaderboardMapping;
}

declare type EAndroidAudio = 'Default' | 'OGG' | 'ADPCM' | 'EAndroidAudio_MAX';
declare var EAndroidAudio : { Default:'Default',OGG:'OGG',ADPCM:'ADPCM',EAndroidAudio_MAX:'EAndroidAudio_MAX', };
declare type EAndroidGraphicsDebugger = 'None' | 'Mali' | 'Adreno' | 'EAndroidGraphicsDebugger_MAX';
declare var EAndroidGraphicsDebugger : { None:'None',Mali:'Mali',Adreno:'Adreno',EAndroidGraphicsDebugger_MAX:'EAndroidGraphicsDebugger_MAX', };
declare class AndroidRuntimeSettings extends UObject { 
	PackageName: string;
	StoreVersion: number;
	StoreVersionOffsetArmV7: number;
	StoreVersionOffsetArm64: number;
	StoreVersionOffsetX8664: number;
	ApplicationDisplayName: string;
	VersionDisplayName: string;
	MinSDKVersion: number;
	TargetSDKVersion: number;
	InstallLocation: EAndroidInstallLocation;
	bEnableGradle: boolean;
	bEnableLint: boolean;
	bPackageDataInsideApk: boolean;
	bCreateAllPlatformsInstall: boolean;
	bDisableVerifyOBBOnStartUp: boolean;
	bForceSmallOBBFiles: boolean;
	bAllowLargeOBBFiles: boolean;
	bAllowPatchOBBFile: boolean;
	bAllowOverflowOBBFiles: boolean;
	bUseExternalFilesDir: boolean;
	bPublicLogFiles: boolean;
	Orientation: EAndroidScreenOrientation;
	MaxAspectRatio: number;
	bUseDisplayCutout: boolean;
	bRestoreNotificationsOnReboot: boolean;
	bFullScreen: boolean;
	bEnableNewKeyboard: boolean;
	DepthBufferPreference: EAndroidDepthBufferPreference;
	bValidateTextureFormats: boolean;
	bForceCompressNativeLibs: boolean;
	bEnableAdvancedBinaryCompression: boolean;
	bEnableBundle: boolean;
	bEnableUniversalAPK: boolean;
	bBundleABISplit: boolean;
	bBundleLanguageSplit: boolean;
	bBundleDensitySplit: boolean;
	ExtraManifestNodeTags: string[];
	ExtraApplicationNodeTags: string[];
	ExtraApplicationSettings: string;
	ExtraActivityNodeTags: string[];
	ExtraActivitySettings: string;
	ExtraPermissions: string[];
	bAndroidVoiceEnabled: boolean;
	PackageForOculusMobile: EOculusMobileDevice[];
	bRemoveOSIG: boolean;
	KeyStore: string;
	KeyAlias: string;
	KeyStorePassword: string;
	KeyPassword: string;
	bBuildForArm64: boolean;
	bBuildForX8664: boolean;
	bBuildForES31: boolean;
	bSupportsVulkan: boolean;
	bSupportsVulkanSM5: boolean;
	DebugVulkanLayerDirectory: DirectoryPath;
	DebugVulkanDeviceLayers: string[];
	DebugVulkanInstanceLayers: string[];
	bAndroidOpenGLSupportsBackbufferSampling: boolean;
	bDetectVulkanByDefault: boolean;
	bBuildWithHiddenSymbolVisibility: boolean;
	bSaveSymbols: boolean;
	bForceLDLinker: boolean;
	bEnableGooglePlaySupport: boolean;
	bUseGetAccounts: boolean;
	GamesAppID: string;
	AchievementMap: GooglePlayAchievementMapping[];
	LeaderboardMap: GooglePlayLeaderboardMapping[];
	bEnableSnapshots: boolean;
	bSupportAdMob: boolean;
	AdMobAdUnitID: string;
	AdMobAdUnitIDs: string[];
	GooglePlayLicenseKey: string;
	GCMClientSenderID: string;
	bShowLaunchImage: boolean;
	bAllowIMU: boolean;
	bAllowControllers: boolean;
	bBlockAndroidKeysOnControllers: boolean;
	bControllersBlockDeviceFeedback: boolean;
	AndroidAudio: EAndroidAudio;
	AudioSampleRate: number;
	AudioCallbackBufferFrameSize: number;
	AudioNumBuffersToEnqueue: number;
	AudioMaxChannels: number;
	AudioNumSourceWorkers: number;
	SpatializationPlugin: string;
	ReverbPlugin: string;
	OcclusionPlugin: string;
	CompressionOverrides: PlatformRuntimeAudioCompressionOverrides;
	CacheSizeKB: number;
	MaxChunkSizeOverrideKB: number;
	bResampleForDevice: boolean;
	SoundCueCookQualityIndex: number;
	MaxSampleRate: number;
	HighSampleRate: number;
	MedSampleRate: number;
	LowSampleRate: number;
	MinSampleRate: number;
	CompressionQualityModifier: number;
	AutoStreamingThreshold: number;
	AndroidGraphicsDebugger: EAndroidGraphicsDebugger;
	MaliGraphicsDebuggerPath: DirectoryPath;
	bEnableMaliPerfCounters: boolean;
	bMultiTargetFormat_ETC2: boolean;
	bMultiTargetFormat_DXT: boolean;
	bMultiTargetFormat_ASTC: boolean;
	TextureFormatPriority_ETC2: number;
	TextureFormatPriority_DXT: number;
	TextureFormatPriority_ASTC: number;
	SDKAPILevelOverride: string;
	NDKAPILevelOverride: string;
	BuildToolsOverride: string;
	bStreamLandscapeMeshLODs: boolean;
	bEnableDomStorage: boolean;
	static Load(ResourceName: string): AndroidRuntimeSettings;
	static Find(Outer: UObject, ResourceName: string): AndroidRuntimeSettings;
	static GetDefaultObject(): AndroidRuntimeSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AndroidRuntimeSettings;
	static C(Other: UObject | any): AndroidRuntimeSettings;
}

declare type EIOSCloudKitSyncStrategy = 'None' | 'OnlyAtGameStart' | 'Always' | 'EIOSCloudKitSyncStrategy_MAX';
declare var EIOSCloudKitSyncStrategy : { None:'None',OnlyAtGameStart:'OnlyAtGameStart',Always:'Always',EIOSCloudKitSyncStrategy_MAX:'EIOSCloudKitSyncStrategy_MAX', };
declare class IOSBuildResourceDirectory { 
	Path: string;
	clone() : IOSBuildResourceDirectory;
	static C(Other: UObject | any): IOSBuildResourceDirectory;
}

declare class IOSBuildResourceFilePath { 
	FilePath: string;
	clone() : IOSBuildResourceFilePath;
	static C(Other: UObject | any): IOSBuildResourceFilePath;
}

declare type EIOSLandscapeOrientation = 'LandscapeLeft' | 'LandscapeRight' | 'EIOSLandscapeOrientation_MAX';
declare var EIOSLandscapeOrientation : { LandscapeLeft:'LandscapeLeft',LandscapeRight:'LandscapeRight',EIOSLandscapeOrientation_MAX:'EIOSLandscapeOrientation_MAX', };
declare type EPowerUsageFrameRateLock = 'PUFRL_None' | 'PUFRL_20' | 'PUFRL_30' | 'PUFRL_60' | 'PUFRL_MAX';
declare var EPowerUsageFrameRateLock : { PUFRL_None:'PUFRL_None',PUFRL_20:'PUFRL_20',PUFRL_30:'PUFRL_30',PUFRL_60:'PUFRL_60',PUFRL_MAX:'PUFRL_MAX', };
declare type EIOSVersion = 'IOS_14' | 'IOS_15' | 'IOS_MAX';
declare var EIOSVersion : { IOS_14:'IOS_14',IOS_15:'IOS_15',IOS_MAX:'IOS_MAX', };
declare class IOSRuntimeSettings extends UObject { 
	bEnableGameCenterSupport: boolean;
	bEnableCloudKitSupport: boolean;
	IOSCloudKitSyncStrategy: EIOSCloudKitSyncStrategy;
	bEnableRemoteNotificationsSupport: boolean;
	bEnableBackgroundFetch: boolean;
	bSupportsMetal: boolean;
	bSupportsMetalMRT: boolean;
	bBuildAsFramework: boolean;
	WindowsMetalToolchainOverride: IOSBuildResourceDirectory;
	bGeneratedSYMFile: boolean;
	bGeneratedSYMBundle: boolean;
	bGenerateCrashReportSymbols: boolean;
	bGenerateXCArchive: boolean;
	bShipForBitcode: boolean;
	bEnableAdvertisingIdentifier: boolean;
	AdditionalLinkerFlags: string;
	AdditionalShippingLinkerFlags: string;
	RemoteServerName: string;
	bUseRSync: boolean;
	RSyncUsername: string;
	RemoteServerOverrideBuildPath: string;
	CwRsyncInstallPath: IOSBuildResourceDirectory;
	SSHPrivateKeyLocation: string;
	SSHPrivateKeyOverridePath: IOSBuildResourceFilePath;
	bRunAsCurrentUser: boolean;
	bGameSupportsMultipleActiveControllers: boolean;
	bAllowRemoteRotation: boolean;
	bUseRemoteAsVirtualJoystick: boolean;
	bUseRemoteAbsoluteDpadValues: boolean;
	bAllowControllers: boolean;
	bControllersBlockDeviceFeedback: boolean;
	bDisableMotionData: boolean;
	bSupportsPortraitOrientation: boolean;
	bSupportsUpsideDownOrientation: boolean;
	bSupportsLandscapeLeftOrientation: boolean;
	bSupportsLandscapeRightOrientation: boolean;
	bSupportsITunesFileSharing: boolean;
	bSupportsFilesApp: boolean;
	PreferredLandscapeOrientation: EIOSLandscapeOrientation;
	BundleDisplayName: string;
	BundleName: string;
	BundleIdentifier: string;
	VersionInfo: string;
	FrameRateLock: EPowerUsageFrameRateLock;
	bEnableDynamicMaxFPS: boolean;
	MinimumiOSVersion: EIOSVersion;
	bSupportsIPad: boolean;
	bSupportsIPhone: boolean;
	AdditionalPlistData: string;
	bCustomLaunchscreenStoryboard: boolean;
	bEnableFacebookSupport: boolean;
	FacebookAppID: string;
	MobileProvision: string;
	SigningCertificate: string;
	bAutomaticSigning: boolean;
	IOSTeamID: string;
	DevCenterUsername: string;
	DevCenterPassword: string;
	bDisableHTTPS: boolean;
	MetalLanguageVersion: number;
	UseFastIntrinsics: boolean;
	ForceFloats: boolean;
	EnableMathOptimisations: boolean;
	IndirectArgumentTier: number;
	bSupportAppleA8: boolean;
	bUseIntegratedKeyboard: boolean;
	AudioSampleRate: number;
	AudioCallbackBufferFrameSize: number;
	AudioNumBuffersToEnqueue: number;
	AudioMaxChannels: number;
	AudioNumSourceWorkers: number;
	SpatializationPlugin: string;
	ReverbPlugin: string;
	OcclusionPlugin: string;
	CompressionOverrides: PlatformRuntimeAudioCompressionOverrides;
	CacheSizeKB: number;
	MaxChunkSizeOverrideKB: number;
	bResampleForDevice: boolean;
	SoundCueCookQualityIndex: number;
	MaxSampleRate: number;
	HighSampleRate: number;
	MedSampleRate: number;
	LowSampleRate: number;
	MinSampleRate: number;
	CompressionQualityModifier: number;
	AutoStreamingThreshold: number;
	bStreamLandscapeMeshLODs: boolean;
	static Load(ResourceName: string): IOSRuntimeSettings;
	static Find(Outer: UObject, ResourceName: string): IOSRuntimeSettings;
	static GetDefaultObject(): IOSRuntimeSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): IOSRuntimeSettings;
	static C(Other: UObject | any): IOSRuntimeSettings;
}

declare class HoloLensCorePackageStringResources { 
	PackageDisplayName: string;
	PublisherDisplayName: string;
	PackageDescription: string;
	ApplicationDisplayName: string;
	ApplicationDescription: string;
	clone() : HoloLensCorePackageStringResources;
	static C(Other: UObject | any): HoloLensCorePackageStringResources;
}

declare class HoloLensCorePackageImageResources { 
	clone() : HoloLensCorePackageImageResources;
	static C(Other: UObject | any): HoloLensCorePackageImageResources;
}

declare class HoloLensCorePackageLocalizedResources { 
	CultureId: string;
	Strings: HoloLensCorePackageStringResources;
	Images: HoloLensCorePackageImageResources;
	clone() : HoloLensCorePackageLocalizedResources;
	static C(Other: UObject | any): HoloLensCorePackageLocalizedResources;
}

declare class HoloLensTargetSettings extends UObject { 
	bBuildForEmulation: boolean;
	bBuildForDevice: boolean;
	bUseNameForLogo: boolean;
	bBuildForRetailWindowsStore: boolean;
	bAutoIncrementVersion: boolean;
	bShouldCreateAppInstaller: boolean;
	AppInstallerInstallationURL: string;
	HoursBetweenUpdateChecks: number;
	bEnablePIXProfiling: boolean;
	TileBackgroundColor: Color;
	SplashScreenBackgroundColor: Color;
	PerCultureResources: HoloLensCorePackageLocalizedResources[];
	TargetDeviceFamily: string;
	MinimumPlatformVersion: string;
	MaximumPlatformVersionTested: string;
	MaxTrianglesPerCubicMeter: number;
	SpatialMeshingVolumeSize: number;
	CompilerVersion: ECompilerVersion;
	Windows10SDKVersion: string;
	CapabilityList: string[];
	DeviceCapabilityList: string[];
	UapCapabilityList: string[];
	Uap2CapabilityList: string[];
	bSetDefaultCapabilities: boolean;
	SpatializationPlugin: string;
	ReverbPlugin: string;
	OcclusionPlugin: string;
	SoundCueCookQualityIndex: number;
	static Load(ResourceName: string): HoloLensTargetSettings;
	static Find(Outer: UObject, ResourceName: string): HoloLensTargetSettings;
	static GetDefaultObject(): HoloLensTargetSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): HoloLensTargetSettings;
	static C(Other: UObject | any): HoloLensTargetSettings;
}

declare class AndroidSDKSettings extends UObject { 
	SDKPath: DirectoryPath;
	NDKPath: DirectoryPath;
	JavaPath: DirectoryPath;
	SDKAPILevel: string;
	NDKAPILevel: string;
	static Load(ResourceName: string): AndroidSDKSettings;
	static Find(Outer: UObject, ResourceName: string): AndroidSDKSettings;
	static GetDefaultObject(): AndroidSDKSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): AndroidSDKSettings;
	static C(Other: UObject | any): AndroidSDKSettings;
}

declare class LogVisualizerSessionSettings extends UObject { 
	bEnableGraphsVisualization: boolean;
	static Load(ResourceName: string): LogVisualizerSessionSettings;
	static Find(Outer: UObject, ResourceName: string): LogVisualizerSessionSettings;
	static GetDefaultObject(): LogVisualizerSessionSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): LogVisualizerSessionSettings;
	static C(Other: UObject | any): LogVisualizerSessionSettings;
}

declare class CategoryFilter { 
	CategoryName: string;
	LogVerbosity: number;
	Enabled: boolean;
	clone() : CategoryFilter;
	static C(Other: UObject | any): CategoryFilter;
}

declare class VisualLoggerFiltersData { 
	SearchBoxFilter: string;
	ObjectNameFilter: string;
	Categories: CategoryFilter[];
	SelectedClasses: string[];
	clone() : VisualLoggerFiltersData;
	static C(Other: UObject | any): VisualLoggerFiltersData;
}

declare class LogVisualizerSettings extends UObject { 
	bIgnoreTrivialLogs: boolean;
	TrivialLogsThreshold: number;
	bStickToRecentData: boolean;
	bResetDataWithNewSession: boolean;
	bShowHistogramLabelsOutside: boolean;
	DefaultCameraDistance: number;
	bSearchInsideLogs: boolean;
	bUseFilterVolumes: boolean;
	GraphsBackgroundColor: Color;
	bPersistentFilters: boolean;
	bDrawExtremesOnGraphs: boolean;
	bConstrainGraphToLocalMinMax: boolean;
	bUsePlayersOnlyForPause: boolean;
	bLogNavOctreeOnStop: boolean;
	bForceUniqueLogNames: boolean;
	PersistentFilters: VisualLoggerFiltersData;
	DebugMeshMaterialFakeLight: Material;
	DebugMeshMaterialFakeLightName: string;
	static Load(ResourceName: string): LogVisualizerSettings;
	static Find(Outer: UObject, ResourceName: string): LogVisualizerSettings;
	static GetDefaultObject(): LogVisualizerSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): LogVisualizerSettings;
	static C(Other: UObject | any): LogVisualizerSettings;
}

declare class VisualLoggerCameraController extends DebugCameraController { 
	PickedActor: Actor;
	static GetDefaultObject(): VisualLoggerCameraController;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): VisualLoggerCameraController;
	static C(Other: UObject | any): VisualLoggerCameraController;
}

declare class VisualLoggerHUD extends DebugCameraHUD { 
	static GetDefaultObject(): VisualLoggerHUD;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): VisualLoggerHUD;
	static C(Other: UObject | any): VisualLoggerHUD;
}

declare class VisualLoggerRenderingActorBase extends Actor { 
	static GetDefaultObject(): VisualLoggerRenderingActorBase;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): VisualLoggerRenderingActorBase;
	static C(Other: UObject | any): VisualLoggerRenderingActorBase;
}

declare class VisualLoggerRenderingActor extends VisualLoggerRenderingActorBase { 
	static GetDefaultObject(): VisualLoggerRenderingActor;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): VisualLoggerRenderingActor;
	static C(Other: UObject | any): VisualLoggerRenderingActor;
}

declare class VisualLoggerRenderingComponent extends DebugDrawComponent { 
	static Load(ResourceName: string): VisualLoggerRenderingComponent;
	static Find(Outer: UObject, ResourceName: string): VisualLoggerRenderingComponent;
	static GetDefaultObject(): VisualLoggerRenderingComponent;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): VisualLoggerRenderingComponent;
	static C(Other: UObject | any): VisualLoggerRenderingComponent;
}

declare class ClothPainterSettings extends MeshPaintSettings { 
	ViewMin: number;
	ViewMax: number;
	bAutoViewRange: boolean;
	AutoCalculatedViewMin: number;
	AutoCalculatedViewMax: number;
	ClothingAssets: ClothingAssetCommon[];
	bFlipNormal: boolean;
	bCullBackface: boolean;
	Opacity: number;
	static Load(ResourceName: string): ClothPainterSettings;
	static Find(Outer: UObject, ResourceName: string): ClothPainterSettings;
	static GetDefaultObject(): ClothPainterSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ClothPainterSettings;
	static C(Other: UObject | any): ClothPainterSettings;
}

declare class ClothPaintTool_BrushSettings extends UObject { 
	PaintValue: number;
	static Load(ResourceName: string): ClothPaintTool_BrushSettings;
	static Find(Outer: UObject, ResourceName: string): ClothPaintTool_BrushSettings;
	static GetDefaultObject(): ClothPaintTool_BrushSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ClothPaintTool_BrushSettings;
	static C(Other: UObject | any): ClothPaintTool_BrushSettings;
}

declare class ClothPaintTool_GradientSettings extends UObject { 
	GradientStartValue: number;
	GradientEndValue: number;
	bUseRegularBrush: boolean;
	static Load(ResourceName: string): ClothPaintTool_GradientSettings;
	static Find(Outer: UObject, ResourceName: string): ClothPaintTool_GradientSettings;
	static GetDefaultObject(): ClothPaintTool_GradientSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ClothPaintTool_GradientSettings;
	static C(Other: UObject | any): ClothPaintTool_GradientSettings;
}

declare class ClothPaintTool_SmoothSettings extends UObject { 
	Strength: number;
	static Load(ResourceName: string): ClothPaintTool_SmoothSettings;
	static Find(Outer: UObject, ResourceName: string): ClothPaintTool_SmoothSettings;
	static GetDefaultObject(): ClothPaintTool_SmoothSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ClothPaintTool_SmoothSettings;
	static C(Other: UObject | any): ClothPaintTool_SmoothSettings;
}

declare class ClothPaintTool_FillSettings extends UObject { 
	Threshold: number;
	FillValue: number;
	static Load(ResourceName: string): ClothPaintTool_FillSettings;
	static Find(Outer: UObject, ResourceName: string): ClothPaintTool_FillSettings;
	static GetDefaultObject(): ClothPaintTool_FillSettings;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ClothPaintTool_FillSettings;
	static C(Other: UObject | any): ClothPaintTool_FillSettings;
}

declare class ActorFactoryLandscape extends ActorFactory { 
	static Load(ResourceName: string): ActorFactoryLandscape;
	static Find(Outer: UObject, ResourceName: string): ActorFactoryLandscape;
	static GetDefaultObject(): ActorFactoryLandscape;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): ActorFactoryLandscape;
	static C(Other: UObject | any): ActorFactoryLandscape;
}

declare type ELandscapeToolFlattenMode = 'Invalid' | 'Both' | 'Raise' | 'Lower' | 'Interval' | 'Terrace' | 'ELandscapeToolFlattenMode_MAX';
declare var ELandscapeToolFlattenMode : { Invalid:'Invalid',Both:'Both',Raise:'Raise',Lower:'Lower',Interval:'Interval',Terrace:'Terrace',ELandscapeToolFlattenMode_MAX:'ELandscapeToolFlattenMode_MAX', };
declare type ELandscapeToolErosionMode = 'Invalid' | 'Both' | 'Raise' | 'Lower' | 'ELandscapeToolErosionMode_MAX';
declare var ELandscapeToolErosionMode : { Invalid:'Invalid',Both:'Both',Raise:'Raise',Lower:'Lower',ELandscapeToolErosionMode_MAX:'ELandscapeToolErosionMode_MAX', };
declare type ELandscapeToolHydroErosionMode = 'Invalid' | 'Both' | 'Positive' | 'ELandscapeToolHydroErosionMode_MAX';
declare var ELandscapeToolHydroErosionMode : { Invalid:'Invalid',Both:'Both',Positive:'Positive',ELandscapeToolHydroErosionMode_MAX:'ELandscapeToolHydroErosionMode_MAX', };
declare type ELandscapeToolNoiseMode = 'Invalid' | 'Both' | 'Add' | 'Sub' | 'ELandscapeToolNoiseMode_MAX';
declare var ELandscapeToolNoiseMode : { Invalid:'Invalid',Both:'Both',Add:'Add',Sub:'Sub',ELandscapeToolNoiseMode_MAX:'ELandscapeToolNoiseMode_MAX', };
declare type ELandscapeToolPasteMode = 'Invalid' | 'Both' | 'Raise' | 'Lower' | 'ELandscapeToolPasteMode_MAX';
declare var ELandscapeToolPasteMode : { Invalid:'Invalid',Both:'Both',Raise:'Raise',Lower:'Lower',ELandscapeToolPasteMode_MAX:'ELandscapeToolPasteMode_MAX', };
declare class GizmoImportLayer { 
	LayerFilename: string;
	LayerName: string;
	bNoImport: boolean;
	clone() : GizmoImportLayer;
	static C(Other: UObject | any): GizmoImportLayer;
}

declare type ELandscapeMirrorOperation = 'MinusXToPlusX' | 'PlusXToMinusX' | 'MinusYToPlusY' | 'PlusYToMinusY' | 'RotateMinusXToPlusX' | 'RotatePlusXToMinusX' | 'RotateMinusYToPlusY' | 'RotatePlusYToMinusY' | 'ELandscapeMirrorOperation_MAX';
declare var ELandscapeMirrorOperation : { MinusXToPlusX:'MinusXToPlusX',PlusXToMinusX:'PlusXToMinusX',MinusYToPlusY:'MinusYToPlusY',PlusYToMinusY:'PlusYToMinusY',RotateMinusXToPlusX:'RotateMinusXToPlusX',RotatePlusXToMinusX:'RotatePlusXToMinusX',RotateMinusYToPlusY:'RotateMinusYToPlusY',RotatePlusYToMinusY:'RotatePlusYToMinusY',ELandscapeMirrorOperation_MAX:'ELandscapeMirrorOperation_MAX', };
declare type ELandscapeConvertMode = 'Invalid' | 'Expand' | 'Clip' | 'Resample' | 'ELandscapeConvertMode_MAX';
declare var ELandscapeConvertMode : { Invalid:'Invalid',Expand:'Expand',Clip:'Clip',Resample:'Resample',ELandscapeConvertMode_MAX:'ELandscapeConvertMode_MAX', };
declare type ELandscapeImportResult = 'Success' | 'Warning' | 'Error' | 'ELandscapeImportResult_MAX';
declare var ELandscapeImportResult : { Success:'Success',Warning:'Warning',Error:'Error',ELandscapeImportResult_MAX:'ELandscapeImportResult_MAX', };
declare type ELandscapeImportTransformType = 'None' | 'ExpandOffset' | 'ExpandCentered' | 'Resample' | 'ELandscapeImportTransformType_MAX';
declare var ELandscapeImportTransformType : { None:'None',ExpandOffset:'ExpandOffset',ExpandCentered:'ExpandCentered',Resample:'Resample',ELandscapeImportTransformType_MAX:'ELandscapeImportTransformType_MAX', };
declare class LandscapeImportResolution { 
	Width: number;
	Height: number;
	clone() : LandscapeImportResolution;
	static C(Other: UObject | any): LandscapeImportResolution;
}

declare class LandscapeFileResolution { 
	Width: number;
	Height: number;
	clone() : LandscapeFileResolution;
	static C(Other: UObject | any): LandscapeFileResolution;
}

declare class LandscapeImportFileDescriptor { 
	Coord: IntPoint;
	FilePath: string;
	clone() : LandscapeImportFileDescriptor;
	static C(Other: UObject | any): LandscapeImportFileDescriptor;
}

declare class LandscapeImportDescriptor { 
	ImportResolutions: LandscapeImportResolution[];
	FileResolutions: LandscapeFileResolution[];
	FileDescriptors: LandscapeImportFileDescriptor[];
	Scale: Vector;
	clone() : LandscapeImportDescriptor;
	static C(Other: UObject | any): LandscapeImportDescriptor;
}

declare type ELandscapeImportAlphamapType = 'Additive' | 'Layered' | 'ELandscapeImportAlphamapType_MAX';
declare var ELandscapeImportAlphamapType : { Additive:'Additive',Layered:'Layered',ELandscapeImportAlphamapType_MAX:'ELandscapeImportAlphamapType_MAX', };
declare class LandscapeImportLayerInfo { 
	LayerName: string;
	LayerInfo: LandscapeLayerInfoObject;
	SourceFilePath: string;
	clone() : LandscapeImportLayerInfo;
	static C(Other: UObject | any): LandscapeImportLayerInfo;
}

declare class LandscapeImportLayer extends LandscapeImportLayerInfo { 
	ThumbnailMIC: LandscapeMaterialInstanceConstant;
	ImportResult: ELandscapeImportResult;
	ErrorMessage: string;
	ExportFilePath: string;
	bSelected: boolean;
	clone() : LandscapeImportLayer;
	static C(Other: UObject | any): LandscapeImportLayer;
}

declare class LandscapePatternBrushWorldSpaceSettings { 
	Origin: Vector2D;
	Rotation: number;
	bCenterTextureOnOrigin: boolean;
	RepeatSize: number;
	clone() : LandscapePatternBrushWorldSpaceSettings;
	static C(Other: UObject | any): LandscapePatternBrushWorldSpaceSettings;
}

declare type EColorChannel = 'Red' | 'Green' | 'Blue' | 'Alpha' | 'EColorChannel_MAX';
declare var EColorChannel : { Red:'Red',Green:'Green',Blue:'Blue',Alpha:'Alpha',EColorChannel_MAX:'EColorChannel_MAX', };
declare class LandscapeEditorObject extends UObject { 
	ToolStrength: number;
	bUseWeightTargetValue: boolean;
	WeightTargetValue: number;
	MaximumValueRadius: number;
	bCombinedLayersOperation: boolean;
	FlattenMode: ELandscapeToolFlattenMode;
	bUseSlopeFlatten: boolean;
	bPickValuePerApply: boolean;
	bUseFlattenTarget: boolean;
	FlattenTarget: number;
	bShowFlattenTargetPreview: boolean;
	TerraceInterval: number;
	TerraceSmooth: number;
	bFlattenEyeDropperModeActivated: boolean;
	FlattenEyeDropperModeDesiredTarget: number;
	RampWidth: number;
	RampSideFalloff: number;
	SmoothFilterKernelSize: number;
	bDetailSmooth: boolean;
	DetailScale: number;
	ErodeThresh: number;
	ErodeSurfaceThickness: number;
	ErodeIterationNum: number;
	ErosionNoiseMode: ELandscapeToolErosionMode;
	ErosionNoiseScale: number;
	RainAmount: number;
	SedimentCapacity: number;
	HErodeIterationNum: number;
	RainDistMode: ELandscapeToolHydroErosionMode;
	RainDistScale: number;
	bHErosionDetailSmooth: boolean;
	HErosionDetailScale: number;
	NoiseMode: ELandscapeToolNoiseMode;
	NoiseScale: number;
	bUseSelectedRegion: boolean;
	bUseNegativeMask: boolean;
	PasteMode: ELandscapeToolPasteMode;
	bApplyToAllTargets: boolean;
	bSnapGizmo: boolean;
	bSmoothGizmoBrush: boolean;
	GizmoHeightmapFilenameString: string;
	GizmoImportSize: IntPoint;
	GizmoImportLayers: GizmoImportLayer[];
	MirrorPoint: Vector2D;
	MirrorOp: ELandscapeMirrorOperation;
	MirrorSmoothingWidth: number;
	BlueprintBrush: UnrealEngineClass;
	ResizeLandscape_QuadsPerSection: number;
	ResizeLandscape_SectionsPerComponent: number;
	ResizeLandscape_ComponentCount: IntPoint;
	ResizeLandscape_ConvertMode: ELandscapeConvertMode;
	NewLandscape_Material: MaterialInterface;
	NewLandscape_QuadsPerSection: number;
	NewLandscape_SectionsPerComponent: number;
	NewLandscape_ComponentCount: IntPoint;
	NewLandscape_Location: Vector;
	NewLandscape_Rotation: Rotator;
	NewLandscape_Scale: Vector;
	ImportLandscape_HeightmapImportResult: ELandscapeImportResult;
	ImportLandscape_HeightmapErrorMessage: string;
	ImportLandscape_HeightmapFilename: string;
	ImportLandscape_Width: number;
	ImportLandscape_Height: number;
	HeightmapExportFilename: string;
	ImportLandscape_GizmoLocalPosition: IntPoint;
	ImportType: ELandscapeImportTransformType;
	bHeightmapSelected: boolean;
	bExportEditLayer: boolean;
	HeightmapImportDescriptor: LandscapeImportDescriptor;
	HeightmapImportDescriptorIndex: number;
	ImportLandscape_Data: number[];
	bCanHaveLayersContent: boolean;
	bFlipYAxis: boolean;
	WorldPartitionGridSize: number;
	ImportLandscape_AlphamapType: ELandscapeImportAlphamapType;
	ImportLandscape_Layers: LandscapeImportLayer[];
	BrushRadius: number;
	BrushFalloff: number;
	bUseClayBrush: boolean;
	AlphaBrushScale: number;
	bAlphaBrushAutoRotate: boolean;
	AlphaBrushRotation: number;
	AlphaBrushPanU: number;
	AlphaBrushPanV: number;
	bUseWorldSpacePatternBrush: boolean;
	WorldSpacePatternBrushSettings: LandscapePatternBrushWorldSpaceSettings;
	AlphaTexture: Texture2D;
	AlphaTextureChannel: EColorChannel;
	AlphaTextureSizeX: number;
	AlphaTextureSizeY: number;
	AlphaTextureData: number[];
	BrushComponentSize: number;
	PaintingRestriction: ELandscapeLayerPaintingRestriction;
	TargetDisplayOrder: ELandscapeLayerDisplayMode;
	ShowUnusedLayers: boolean;
	CurrentLayerIndex: number;
	static Load(ResourceName: string): LandscapeEditorObject;
	static Find(Outer: UObject, ResourceName: string): LandscapeEditorObject;
	static GetDefaultObject(): LandscapeEditorObject;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): LandscapeEditorObject;
	static C(Other: UObject | any): LandscapeEditorObject;
}

declare class LandscapePlaceholder extends Actor { 
	static GetDefaultObject(): LandscapePlaceholder;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): LandscapePlaceholder;
	static C(Other: UObject | any): LandscapePlaceholder;
}

declare class PLACEHOLDER-CLASS__UI_MovieRenderPipelineInfoTableRow_C_0 { 
	constructor();
	constructor(Outer: UObject);
	static Load(ResourceName: string): PLACEHOLDER-CLASS__UI_MovieRenderPipelineInfoTableRow_C_0;
	static Find(Outer: UObject, ResourceName: string): PLACEHOLDER-CLASS__UI_MovieRenderPipelineInfoTableRow_C_0;
	static StaticClass: any;
	static GetClassObject(): Class;
	static GetDefaultObject(): PLACEHOLDER-CLASS__UI_MovieRenderPipelineInfoTableRow_C_0;
	static GetDefaultSubobjectByName(Name: string): UObject;
	static SetDefaultSubobjectClass(Name: string): void;
	static CreateDefaultSubobject(Name: string, Transient?: boolean, Required?: boolean, Abstract?: boolean): PLACEHOLDER-CLASS__UI_MovieRenderPipelineInfoTableRow_C_0;
	static C(Other: UObject | any): PLACEHOLDER-CLASS__UI_MovieRenderPipelineInfoTableRow_C_0;
}

declare var Context : JavascriptContext;

declare var Root : JavascriptEditorTick;


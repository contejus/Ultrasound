#import <UIKit/UIKit.h>
#import "ABVolumeHUDManager.h"
#import "ABVolumeHUDWindow.h"
#import "ABVolumeHUDViewSettings.h"
#import "ABVolumeHUDDeviceInfo.h"
#import "ABVolumeHUDSystemVolumeInfoProvider.h"
#import "ABVolumeHUDSystemTapticFeedbackProvider.h"
#import "dlfcn.h"

@interface AVSystemController : NSObject
+ (instancetype)sharedAVSystemController;
- (BOOL)getVolume:(float *)volume forCategory:(NSString *)category;
- (BOOL)setVolumeTo:(float)volume forCategory:(NSString *)category;
@end

@interface SBMediaController : NSObject
+ (instancetype)sharedInstance;
- (BOOL)isRingerMuted;
@end

@interface SBBacklightController : NSObject
@property (nonatomic,readonly) BOOL screenIsOn;
+ (instancetype)sharedInstance;
- (void)turnOnScreenFullyWithBacklightSource:(long long)arg1;
- (void)_animateBacklightToFactor:(float)factor duration:(double)duration source:(long long)source silently:(BOOL)silently completion:(/*^block*/id)completion;
- (void)setBacklightFactor:(float)factor source:(long long)arg2;
- (void)allowIdleSleep;
- (void)preventIdleSleep;
@end

@interface SBLockScreenViewControllerBase : UIViewController
-(BOOL)isInScreenOffMode;
-(BOOL)isShowingMediaControls;
@end

@interface SBLockScreenManager : NSObject
@property (readonly) BOOL isUILocked;
+ (instancetype)sharedInstance;
- (SBLockScreenViewControllerBase *)lockScreenViewController;
- (BOOL)unlockUIFromSource:(int)source withOptions:(NSDictionary *)options;
@end

@interface VolumeControl : NSObject
+ (instancetype)sharedVolumeControl;
- (float)getMediaVolume;
- (void)setMediaVolume:(float)volume;
- (void)_presentVolumeHUDWithMode:(int)mode volume:(float)volume;
@end

@interface SBLiftToWakeManager : NSObject
@property (setter=_setLockScreenManager:,getter=_lockScreenManager,nonatomic,retain) SBLockScreenManager *lockScreenManager;  
@end

@interface SBScreenWakeAnimationController : NSObject
+ (instancetype)sharedInstance;
- (void)_startWakeIfNecessary;
@end;

@interface SBUIBiometricResource : NSObject
+ (instancetype)sharedInstance;
- (BOOL)isPearlDetectEnabled;
- (void)noteScreenWillTurnOn;
@end

@interface SBFTapticEngine : NSObject
+ (id)sharedInstance;
-(void)actuateFeedback:(long long)arg1 ;
-(BOOL)supportsFeedbackActuation;
-(void)warmUpForFeedback:(unsigned long long)arg1 withReason:(id)arg2 ;
-(void)coolDownForFeedback:(unsigned long long)arg1 withReason:(id)arg2 ;
@end

@interface SBTapToWakeController : NSObject
+(BOOL)isTapToWakeSupported;
@end

@protocol SBUIActiveOrientationObserver <NSObject>
@required
-(void)activeInterfaceOrientationWillChangeToOrientation:(UIInterfaceOrientation)orientation;
-(void)activeInterfaceOrientationDidChangeToOrientation:(UIInterfaceOrientation)orientation willAnimateWithDuration:(NSTimeInterval)duration fromOrientation:(UIInterfaceOrientation)previousOrientation;
@end

@interface SpringBoard : UIApplication
- (UIInterfaceOrientation)activeInterfaceOrientation;
- (void)addActiveOrientationObserver:(NSObject <SBUIActiveOrientationObserver>*)observer;
@end
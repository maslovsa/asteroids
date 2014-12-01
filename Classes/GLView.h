#import "IRenderingEngine.hpp"
#import <QuartzCore/QuartzCore.h>

@interface GLView : UIView {
@private
    EAGLContext* m_context;
    IRenderingEngine* m_renderingEngine;
    float m_timestamp;
}
- (void) didRotate: (NSNotification*) notification;
- (void) drawView: (CADisplayLink*) displayLink;

@end

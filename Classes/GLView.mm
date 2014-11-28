#import "GLView.h"
#import <OpenGLES/ES2/gl.h>

@implementation GLView

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *) super.layer;
        eaglLayer.opaque = YES;

        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        m_context = [[EAGLContext alloc] initWithAPI:api];

        if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
            [self release];
            return nil;
        }

        m_renderingEngine = CreateRenderer();

        [m_context
                    renderbufferStorage:GL_RENDERBUFFER
                           fromDrawable:eaglLayer];

        m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        NSLog(@"w=%f h=%f", CGRectGetWidth(frame), CGRectGetHeight(frame));
        [self drawView:nil];
        m_timestamp = CACurrentMediaTime();

        CADisplayLink *displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self
                                                  selector:@selector(drawView:)];

        [displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                          forMode:NSDefaultRunLoopMode];
    }
    return self;
}

- (void)drawView:(CADisplayLink *)displayLink {
    if (displayLink != nil) {
        float elapsedSeconds = displayLink.timestamp - m_timestamp;
        m_timestamp = displayLink.timestamp;
        m_renderingEngine->UpdateAnimation(elapsedSeconds);
    }

    m_renderingEngine->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInView:self];
    m_renderingEngine->OnFingerDown(ivec2(location.x, location.y));
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInView:self];
    m_renderingEngine->OnFingerUp(ivec2(location.x, location.y));
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    CGPoint previous = [touch previousLocationInView:self];
    CGPoint current = [touch locationInView:self];
    m_renderingEngine->OnFingerMove(ivec2(previous.x, previous.y),
                                    ivec2(current.x, current.y));
}

@end

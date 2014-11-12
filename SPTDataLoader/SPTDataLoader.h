#import <Foundation/Foundation.h>

@class SPTDataLoaderRequest;
@class SPTDataLoaderResponse;
@class SPTDataLoader;

@protocol SPTCancellationToken;

/**
 * The protocol used for listening to the result of performing requests on the SPTDataLoader
 * @discussion One of the following callbacks are guaranteed to happen for every request being track by the data loader:
 * - didReceiveSuccessfulResponse
 * - didReceiveErrorResponse
 * - didCancelRequest
 */
@protocol SPTDataLoaderDelegate <NSObject>

/**
 * Called when the data loader received a successful response
 * @param dataLoader The data loader that received the successful response
 * @param response The object describing the response
 */
- (void)dataLoader:(SPTDataLoader *)dataLoader didReceiveSuccessfulResponse:(SPTDataLoaderResponse *)response;
/**
 * Called when the data loader received an error response
 * @param dataLoader The data loader that received the error response
 * @param response The object describing the response
 */
- (void)dataLoader:(SPTDataLoader *)dataLoader didReceiveErrorResponse:(SPTDataLoaderResponse *)response;
/**
 * Called when the data loader cancels a request
 * @param dataLoader The data loader that cancelled the request
 * @param request The object describing the request that was cancelled
 */
- (void)dataLoader:(SPTDataLoader *)dataLoader didCancelRequest:(SPTDataLoaderRequest *)request;

@optional

/**
 * Whether the data loader delegate will support chunks being called back
 * @param dataLoader The data loader asking the delegate for its support
 */
- (BOOL)dataLoaderShouldSupportChunks:(SPTDataLoader *)dataLoader;
/**
 * Called when the data loader receives a chunk of data for a request
 * @param dataLoader The data loader that receives the chunk
 * @param data The data that the data loader received
 * @param request The request that generated the data
 */
- (void)dataLoader:(SPTDataLoader *)dataLoader
didReceiveDataChunk:(NSData *)data
        forRequest:(SPTDataLoaderRequest *)request;

@end

/**
 * The object used for performing requests
 */
@interface SPTDataLoader : NSObject

/**
 * The object listening to the data loader
 */
@property (nonatomic, weak) id<SPTDataLoaderDelegate> delegate;

/**
 * Performs a request
 * @param request The object describing the kind of request to be performed
 */
- (id<SPTCancellationToken>)performRequest:(SPTDataLoaderRequest *)request;
/**
 * Cancels all the currently operating and pending requests
 */
- (void)cancelAllLoads;

@end

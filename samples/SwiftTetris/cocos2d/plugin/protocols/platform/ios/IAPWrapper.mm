/****************************************************************************
Copyright (c) 2014 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#import "IAPWrapper.h"
#include "PluginUtilsIOS.h"
#include "ProtocolIAP.h"
#import <StoreKit/StoreKit.h>

using namespace cocos2d::plugin;

@implementation IAPWrapper

+ (void) onPayResult:(id) obj withRet:(IAPResult) ret withMsg:(NSString*) msg
{
    PluginProtocol* plugin = PluginUtilsIOS::getPluginPtr(obj);
    ProtocolIAP* iapPlugin = dynamic_cast<ProtocolIAP*>(plugin);
    if (iapPlugin) {
        const char* chMsg = [msg UTF8String];
        PayResultCode cRet = (PayResultCode) ret;
        iapPlugin->onPayResult(cRet, chMsg);
    } else {
        PluginUtilsIOS::outputLog("Can't find the C++ object of the IAP plugin");
    }
}
+(void) onRequestProduct:(id)obj withRet:(ProductRequest) ret withProducts:(NSArray *)products{
    PluginProtocol* plugin = PluginUtilsIOS::getPluginPtr(obj);
    ProtocolIAP* iapPlugin = dynamic_cast<ProtocolIAP*>(plugin);
    if (iapPlugin) {
        TProductList pdlist;
        if (products) {
            for(SKProduct *product in products){
                TProductInfo info;
                info.insert(std::make_pair("productId", std::string([product.productIdentifier UTF8String])));
                info.insert(std::make_pair("productName", std::string([product.localizedTitle UTF8String])));
                info.insert(std::make_pair("productPrice", std::string([[product.price stringValue] UTF8String])));
                info.insert(std::make_pair("productDesc", std::string([product.localizedDescription UTF8String])));
                pdlist.push_back(info);
            }
        }
        iapPlugin->getResultListener()->onRequestProductsResult((IAPProductRequest )ret,pdlist);
    } else {
        PluginUtilsIOS::outputLog("Can't find the C++ object of the IAP plugin");
    }

}
@end

/**
 * @file Browser bindings generated by 'generate_bindings.py', DO NOT EDIT!
 */

var bm;

(function (bm) {
    bm.common = {
        getCVar: cwrap('common_getCVar', 'number', ['string']),
        log: cwrap('common_log', 'undefined', ['string']),
        setCVar: cwrap('common_setCVar', 'number', ['string', 'number'])
    };
})(bm || (bm = {}));

  

(function() {
        // Fake loading.
        setTimeout(init, 1000);


        function init() {
            document.body.classList.remove('loading');

            var element = document.getElementById('rev-1'),
                watcher = scrollMonitor.create(element, -(element.offsetHeight)),
                //mediaToolbar = document.querySelector('.media__toolbar'),
                duration = 1200,
                rev1 = new RevealFx(element, {
                    revealSettings: {
                        direction: 'tb',
                        bgcolor: '#212121',
                        duration: duration/3,
                        easing: 'easeInOutCirc',
                        coverArea: 100,
                        revealWidth: '12px',
                        /** Callback for when the revealer is covering the element (halfway through of the whole animation). */
                        onCover: function (_contentEl, _revealerEl) {
                            console.log('Element has being covered.');
                            anime({
                                targets: _revealerEl,
                                width: {
                                    value: _contentEl.offsetWidth,
                                    duration: duration/3,
                                },
                                easing: 'easeInOutQuad',
                                complete: function() {
                                    _contentEl.style.opacity = 1;
                                    anime({
                                        targets: _revealerEl,
                                        width: {
                                            value: 0,
                                            duration: duration/3
                                        },
                                        translateX:{
                                            value: _contentEl.offsetWidth,
                                            duration: duration/3
                                        },
                                        easing: 'easeInOutQuad'
                                    });
                                }
                            });
                        },
                        /** Callback for when the animation starts (animation start).*/
                        /** onStart: function(_contentEl, _revealerEl) { return false; }, */
                        /** Callback for when the revealer has completed uncovering (animation end). */
                        onComplete: function(_contentEl, _revealerEl) {
                            console.log('Element has being completed.');
                        }
                    }
                });

            watcher.enterViewport(function() {
                rev1.reveal();
                watcher.destroy();
            });

            /** ======================================================= */
            var element2 = document.getElementById('rev-2'),
                watcher2 = scrollMonitor.create(element2, -(element2.offsetHeight)),
                duration2 = 1200,
                rev2 = new RevealFx(element2, {
                    revealSettings: {
                        direction: 'tb',
                        bgcolor: '#212121',
                        duration: duration2/3,
                        easing: 'easeInOutCirc',
                        coverArea: 100,
                        revealWidth: '12px',
                        /** Callback for when the revealer is covering the element (halfway through of the whole animation). */
                        onCover: function (_contentEl, _revealerEl) {
                            console.log('Element has being covered.');
                            anime({
                                targets: _revealerEl,
                                width: {
                                    value: _contentEl.offsetWidth,
                                    duration: duration2/3,
                                },
                                easing: 'easeInOutQuad',
                                complete: function() {
                                    _contentEl.style.opacity = 1;
                                    anime({
                                        targets: _revealerEl,
                                        width: {
                                            value: 0,
                                            duration: duration2/3
                                        },
                                        translateX:{
                                            value: _contentEl.offsetWidth,
                                            duration: duration2/3
                                        },
                                        easing: 'easeInOutQuad'
                                    });
                                }
                            });
                        },
                        /** Callback for when the animation starts (animation start).*/
                        /** onStart: function(_contentEl, _revealerEl) { return false; }, */
                        /** Callback for when the revealer has completed uncovering (animation end). */
                        onComplete: function(_contentEl, _revealerEl) {
                            console.log('Element has being completed.');
                        }
                    }
                });

            watcher2.enterViewport(function() {
                rev2.reveal();
                watcher2.destroy();
            });

        }


})(jQuery);
	
	
	
	
	
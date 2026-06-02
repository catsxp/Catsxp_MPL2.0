import { isMac, isChromeOS } from 'chrome://resources/js/platform.js';
import { loadTimeData } from '../i18n_setup.js';

// 定义全局变量 page_ 的类型
let page_: {
    $$: (selector: string) => HTMLElement | null;
    set: (key: string, value: any) => void;
    root: HTMLElement;
} | null = null;

// 定义 chrome 对象的类型
declare const chrome: {
    send: (method: string, args: any[]) => void;
};

enum Modifiers {
    ARE_NOT_ALLOWED = 0,
    ARE_REQUIRED = 1
}

// 预定义有效特殊键的集合
const validSpecialKeys = new Set<string>([
    ',', 'Delete', 'ArrowDown', 'End', 'Home', 'Insert', 'ArrowLeft',
    'MediaNextTrack', 'MediaPlayPause', 'MediaPrevTrack', 'MediaStop',
    'PageDown', 'PageUp', '.', 'ArrowRight', ' ', 'Tab', 'ArrowUp', '`',
    'F1', 'F2', 'F3', 'F4', 'F5', 'F6', 'F7', 'F8', 'F9', 'F10', 'F11', 'F12'
]);

// 键位映射表
const keyMap: { [key: string]: string } = {
    ',': 'Comma',
    'Delete': 'Delete',
    'ArrowDown': 'Down',
    'End': 'End',
    'Home': 'Home',
    'Insert': 'Insert',
    'ArrowLeft': 'Left',
    'MediaNextTrack': 'MediaNextTrack',
    'MediaPlayPause': 'MediaPlayPause',
    'MediaPrevTrack': 'MediaPrevTrack',
    'MediaStop': 'MediaStop',
    'PageDown': 'PageDown',
    'PageUp': 'PageUp',
    '.': 'Period',
    'ArrowRight': 'Right',
    ' ': 'Space',
    'Tab': 'Tab',
    'ArrowUp': 'Up',
    'F1': 'F1',
    'F2': 'F2',
    'F3': 'F3',
    'F4': 'F4',
    'F5': 'F5',
    'F6': 'F6',
    'F7': 'F7',
    'F8': 'F8',
    'F9': 'F9',
    'F10': 'F10',
    'F11': 'F11',
    'F12': 'F12',
    '`': '`'
};

// 媒体键集合
const mediaKeys = new Set<string>(['MediaNextTrack', 'MediaPlayPause', 'MediaPrevTrack', 'MediaStop']);

function validChar(key: string): boolean {
    return validSpecialKeys.has(key) || /^[a-zA-Z0-9]$/.test(key);
}

function keystrokeToString(event: KeyboardEvent): string {
    const output: string[] = [];

    // 处理修饰键
    if (event.metaKey) {
        if (isMac) output.push('Command');
        else output.push('Meta');
    }
    if (event.ctrlKey) output.push('Ctrl');
    if (event.altKey) output.push('Alt');
    if (event.shiftKey) output.push('Shift');

    // 处理主键
    const key = event.key;
    if (validChar(key)) {
        const mappedKey = keyMap[key];
        if (mappedKey !== undefined) {
            output.push(mappedKey);
        } else if (/^[a-zA-Z0-9]$/.test(key)) {
            output.push(key.toUpperCase());
        }
    }

    return output.join('+') || '';
}

function modifiers(key: string): Modifiers {
    return mediaKeys.has(key) ? Modifiers.ARE_NOT_ALLOWED : Modifiers.ARE_REQUIRED;
}

function hasModifier(event: KeyboardEvent, countShiftAsModifier: boolean): boolean {
    return event.ctrlKey || event.altKey || (isMac && event.metaKey) ||
        (isChromeOS && event.metaKey) || (countShiftAsModifier && event.shiftKey);
}

export class BossKeyBindingController {
    private currentKeyEvent_: KeyboardEvent | null = null;
    private oldValue_: string = '';
    private capturingElement_: HTMLElement | null = null;

    constructor(page: any) {
        page_ = page;
        const textnode = page_!.root.querySelector('#catsxp-boss-key-command-text') as HTMLElement;
        if (!textnode) {
            throw new Error('Element #catsxp-boss-key-command-text not found');
        }
        textnode.addEventListener('mouseup', this.startCapture_.bind(this));
        textnode.addEventListener('focus', this.handleFocus_.bind(this));
        textnode.addEventListener('blur', this.handleBlur_.bind(this));
        textnode.addEventListener('keydown', this.handleKeyDown_.bind(this));
        textnode.addEventListener('keyup', this.handleKeyUp_.bind(this));
    }

    private startCapture_(event: Event): void {
        if (this.capturingElement_) return;
        const textnode = page_!.root.querySelector('#catsxp-boss-key-command-text') as HTMLElement;
        this.oldValue_ = textnode.textContent || '';
        const defaultString = loadTimeData.getString('bossKeyCommandConfigInput');
        textnode.textContent = defaultString;
        this.capturingElement_ = event.target as HTMLElement;
    }

    private endCapture_(): void {
        if (!this.capturingElement_) return;
        const textnode = page_!.root.querySelector('#catsxp-boss-key-command-text') as HTMLElement;
        const bossKeyCommand = page_!.root.querySelector('#catsxp-boss-key-command') as HTMLElement;
        bossKeyCommand.classList.remove('catsxp-boss-key-contains-chars');
        if (!this.currentKeyEvent_ || !validChar(this.currentKeyEvent_.key)) {
            textnode.textContent = this.oldValue_;
        }
        this.oldValue_ = '';
        this.capturingElement_ = null;
        this.currentKeyEvent_ = null;
    }

    private handleFocus_(): void {
    }

    private handleBlur_(): void {
        this.endCapture_();
    }

    private handleKeyDown_(event: KeyboardEvent): void {
        if (event.key === 'Escape') {
            this.endCapture_();
            event.preventDefault();
            event.stopPropagation();
            return;
        }
        if (event.key === 'Tab') return;
        if (!this.capturingElement_) this.startCapture_(event);
        this.handleKey_(event);
    }

    private handleKeyUp_(event: KeyboardEvent): void {
        if (event.key === 'Tab') return;
        if (this.currentKeyEvent_ && !validChar(this.currentKeyEvent_.key)) {
            if (!event.ctrlKey && !event.altKey || ((isMac || isChromeOS) && !event.metaKey)) {
                this.endCapture_();
                this.startCapture_(event);
            } else {
                this.handleKey_(event);
            }
        }
    }

    private handleKey_(event: KeyboardEvent): void {
        event.preventDefault();
        event.stopPropagation();
        if (modifiers(event.key) === Modifiers.ARE_REQUIRED && !hasModifier(event, false)) return;
        if (modifiers(event.key) === Modifiers.ARE_NOT_ALLOWED && hasModifier(event, true)) return;

        const textnode = page_!.root.querySelector('#catsxp-boss-key-command-text') as HTMLElement;
        const keystroke = keystrokeToString(event);
        textnode.textContent = keystroke;
        (event.target as HTMLElement).classList.add('catsxp-boss-key-contains-chars');
        this.currentKeyEvent_ = event;

        if (validChar(event.key)) {
            this.oldValue_ = keystroke;
            this.endCapture_();
            page_!.set('prefs.catsxp.accelerator.boss_key_command_text.value', keystroke);
            textnode.blur();
        }
    }
}

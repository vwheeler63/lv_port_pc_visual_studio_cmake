#include <Windows.h>

#include "../lvgl/lvgl.h"
#include "../lvgl/examples/lv_examples.h"
#include "../lvgl/demos/lv_demos.h"

int main(void)
{
    lv_init();

    /*
     * Optional workaround for users who wants UTF-8 console output.
     * If you don't want that behavior can comment them out.
     *
     * Suggested by jinsc123654.
     */
#if LV_TXT_ENC == LV_TXT_ENC_UTF8
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int32_t zoom_level = 100;
    bool allow_dpi_override = false;
    bool simulator_mode = true;
    lv_display_t* display = lv_windows_create_display(
        L"LVGL Windows Simulator Display 1",
        800,
        480,
        zoom_level,
        allow_dpi_override,
        simulator_mode);
    if (!display)
    {
        return -1;
    }

    HWND window_handle = lv_windows_get_display_window_handle(display);
    if (!window_handle)
    {
        return -1;
    }

    HICON icon_handle = LoadIcon(
        GetModuleHandleW(NULL),
        "IDI_LVGL_WINDOWS");

    if (icon_handle)
    {
        SendMessageW(
            window_handle,
            WM_SETICON,
            TRUE,
            (LPARAM)icon_handle);
        SendMessageW(
            window_handle,
            WM_SETICON,
            FALSE,
            (LPARAM)icon_handle);
    }

    lv_indev_t* pointer_indev = lv_windows_acquire_pointer_indev(display);
    if (!pointer_indev)
    {
        return -1;
    }

    lv_indev_t* keypad_indev = lv_windows_acquire_keypad_indev(display);
    if (!keypad_indev)
    {
        return -1;
    }

    lv_indev_t* encoder_indev = lv_windows_acquire_encoder_indev(display);
    if (!encoder_indev)
    {
        return -1;
    }

    lv_demo_widgets();
    // All shipped demos and examples can be found in these directories:
    // - lvgl/demos/
    // - lvgl/examples/
    //
    // To use them, simply comment out `lv_demo_widgets()` above and call
    // their function.  As of March 2026, there are 14 demos 231 examples.
    // The easy way:  use Visual Studio's intellisense by start typing
    // "lv_example_" or "lv_demo_" and use the pop-up list to select from.
    //
    // Benchmark
    // =========
    // lv_demo_benchmark();
    //
    // Basic Examples
    // ==============
    // lv_example_get_started_1();
    // lv_example_get_started_2();
    // lv_example_get_started_3();
    // lv_example_get_started_4();
    //
    // Subset of Widget Examples
    // =========================
    // lv_example_bar_1();
    // lv_example_button_1();
    // lv_example_buttonmatrix_1();
    // lv_example_checkbox_1();
    // lv_example_dropdown_1();
    // lv_example_calendar_1();
    // lv_example_canvas_1();
    // lv_example_image_1();
    // lv_example_keyboard_1();
    // lv_example_label_1();
    // lv_example_led_1();
    // lv_example_list_1();
    // lv_example_msgbox_1();
    // lv_example_obj_1();
    // lv_example_roller_1();
    // lv_example_scale_1();
    // lv_example_slider_1();
    // lv_example_spinbox_1();
    // lv_example_spinner_1();
    // lv_example_switch_1();
    // lv_example_table_1();
    // lv_example_tabview_1();
    // lv_example_textarea_1();
    // lv_example_tileview_1();
    // lv_example_win_1();
    //
    // Layout Examples
    // ===============
    // lv_example_flex_1();
    // lv_example_grid_1();
    //
    // Styles (as of March 2026 there are 21 of these)
    // ===============================================
    // lv_example_style_1();
    //
    // Observer (as of March 2026 there are 7 of these)
    // ================================================
    // lv_example_observer_1();
    //
    // Also, check out:
    // ================
    // - lvgl/examples/event/
    // - lvgl/examples/libs/
    // - lvgl/examples/anim/
    // - etc.
    //
    // And there are dozens more.

    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        lv_delay_ms(time_till_next);
    }

    return 0;
}

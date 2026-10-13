import unittest

from arknights_probe.coroutines import CoroutineRunner, NEXT_FRAME, fixed_seconds, float_wait_frames, serial_queue, wait_while


class CoroutineTests(unittest.TestCase):
    def test_zero_wait_and_do_while_cost_one_frame(self):
        self.assertEqual(float_wait_frames(0, 0.25), 1)
        self.assertEqual(float_wait_frames(0.26, 0.25), 1)
        self.assertEqual(float_wait_frames(.625, .25), 2)  # 2.5 -> even
        self.assertEqual(float_wait_frames(.875, .25), 4)  # 3.5 -> even
        calls = []
        runner = CoroutineRunner(wait_while(lambda: calls.append(True) or False))
        self.assertTrue(runner.tick())
        self.assertEqual(calls, [])
        self.assertFalse(runner.tick())
        self.assertEqual(calls, [True])

    def test_empty_first_child_suspends_parent(self):
        events = []
        def empty():
            if False:
                yield
        def root():
            events.append("before")
            yield empty()
            events.append("after")
            yield NEXT_FRAME
        runner = CoroutineRunner(root())
        self.assertTrue(runner.tick())
        self.assertEqual(events, ["before"])
        self.assertTrue(runner.tick())
        self.assertEqual(events, ["before", "after"])
        self.assertFalse(runner.tick())

    def test_same_planned_time_is_serial(self):
        events = []
        runner = None
        def execute(item):
            events.append((runner.ticks, item["key"]))
            yield NEXT_FRAME
        runner = CoroutineRunner(serial_queue([{"time": 0, "key": "a"}, {"time": 0, "key": "b"}], execute, .25))
        runner.tick()
        self.assertEqual(events, [(1, "a")])
        runner.tick()
        self.assertEqual(events, [(1, "a"), (2, "b")])
        self.assertFalse(runner.tick())

    def test_waits_use_planned_delta_not_wall_time(self):
        events = []
        runner = None
        def execute(item):
            events.append(runner.ticks)
            yield NEXT_FRAME
        runner = CoroutineRunner(serial_queue([{"time": 1}, {"time": 2}], execute, .25))
        while runner.active:
            runner.tick()
        self.assertEqual(events, [5, 10])

    def test_nested_wait_returns_same_frame(self):
        events = []
        def root():
            yield fixed_seconds(0, .25)
            events.append(True)
        runner = CoroutineRunner(root())
        self.assertTrue(runner.tick())
        self.assertFalse(runner.tick())
        self.assertEqual(events, [True])


if __name__ == "__main__":
    unittest.main()
